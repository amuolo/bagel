//
// Author : Toru Shiozaki
// Date   : Dec 2011
//

#include <src/casscf/superci.h>
#include <iostream>
#include <src/fci/fci.h>
#include <src/casscf/rotfile.h>
#include <src/util/davidson.h>
#include <src/scf/hcore.h>
#include <src/scf/fock.h>
#include <src/scf/scf.h>
#include <src/util/f77.h>
#include <src/util/hpw_diis.h>

using namespace std;

SuperCI::SuperCI(const multimap<string, string> idat, const shared_ptr<Geometry> geom)
 : CASSCF(idat, geom) {
  common_init();
}

SuperCI::SuperCI(const multimap<string, string> idat, const shared_ptr<Geometry> geom, const shared_ptr<SCF> scf)
 : CASSCF(idat, geom, scf) {
  common_init();
}

void SuperCI::common_init() {
  cout << "    * Using the Super CI algorithm as noted in Roos (1980) IJQC" << endl;
  // get maxiter from the input
  diis_start_ = read_input<int>(idata_, "diis_start", 5);
  cout << "    * DIIS will be used after " << diis_start_ << " macro iteration" << endl << endl;
}

SuperCI::~SuperCI() {

}


void SuperCI::compute() {
  const string indent = "  ";

  cout << indent << "=== CASSCF iteration (" + geom_->basisfile() + ")===" << endl << endl;
  // 0 means not converged
  vector<int> conv(nstate_,0);

  // initializing Hcore matrix (redundant copy, but I can live with it).
  shared_ptr<Fock> hcore_;
  {
    shared_ptr<Hcore> hc(new Hcore(geom_));
    shared_ptr<Fock> fc(new Fock(geom_, hc)); hcore_ = fc;
  }

  // DIIS: will be turned on at iter = diis_start_ (>1), 
  //       update log(U) where Cnow = Corig U. This is basically the same as the Hampel-Peterson-Werner
  //       paper on Brueckner CC
  shared_ptr<HPW_DIIS<Matrix1e> > diis;

  // ============================
  // macro iteration from here
  // ============================
  for (int iter = 0; iter != max_iter_; ++iter) {
    int start = ::clock();

    if (iter == diis_start_) {
      shared_ptr<Matrix1e> tmp(new Matrix1e(*ref_->coeff()));
      shared_ptr<HPW_DIIS<Matrix1e> > d(new HPW_DIIS<Matrix1e>(5, tmp));
      diis = d;
    }

    // first perform CASCI to obtain RDMs
    mute_stdcout();
    fci_->compute();
    fci_->compute_rdm12();
    resume_stdcout();
    // get energy
    vector<double> energy = fci_->energy();

    // slot in density matrix
    shared_ptr<Matrix1e> denall = ao_rdm1(fci_->rdm1_av());
    shared_ptr<Matrix1e> deninact = ao_rdm1(fci_->rdm1_av(), true); // true means inactive_only

    // here make a natural orbitals and update the coefficients
    // this effectively updates 1,2RDM and integrals
    const pair<vector<double>, vector<double> > natorb = fci_->natorb_convert();
    // new coefficients
    shared_ptr<Coeff> new_coeff = update_coeff(ref_->coeff(), natorb.first);
    ref_->set_coeff(new_coeff);
    // occupation number of the natural orbitals
    occup_ = natorb.second;
#if 0
    if (std::abs(occup_.front()-2.0) < 1.0e-16 || std::abs(occup_.back()) < 1.0e-16)
      throw runtime_error("CASSCF does not work so far if occupied orbitals are strictly doubly occupied or empty.");
#endif

    // get quantity Q_xr = 2(xs|tu)P_rs,tu (x=general)
    // note: this should be after natorb transformation.
    shared_ptr<QFile> qxr(new QFile(nbasis_, nact_));
    compute_qxr(fci_->jop()->mo2e_1ext_ptr(), fci_->rdm2_av(), qxr);

    shared_ptr<RotFile> cc_(new RotFile(nclosed_, nact_, nvirt_));
    double gradient;
    
    // Davidson utility. We diagonalize a super CI matrix every macro iteration
    DavidsonDiag<RotFile> davidson(1, max_micro_iter_);
    shared_ptr<RotFile> sigma_(new RotFile(nclosed_, nact_, nvirt_));

    // computes f and f_act
    // TODO call to fock builder should be done only once.
    shared_ptr<Matrix1e> f, finact;
    shared_ptr<QFile>    fact, factp, gaa;
    shared_ptr<Coeff> coeff = ref_->coeff();
    {
      // Fock operator
      shared_ptr<Fock> f_ao(new Fock(geom_, hcore_, denall, ref_->schwarz()));
      shared_ptr<Matrix1e> ft(new Matrix1e(*coeff % *f_ao * *coeff)); f = ft;
    }
    {
      // inactive Fock operator
      shared_ptr<Fock> finact_ao(new Fock(geom_, hcore_, deninact, ref_->schwarz()));
      shared_ptr<Matrix1e> ft(new Matrix1e(*coeff % *finact_ao * *coeff)); finact = ft;
    }
    {
      // active-x Fock operator Dts finact_sx + Qtx
      shared_ptr<QFile> ft(new QFile(*qxr)); fact = ft; // nbasis_ runs first
      for (int i = 0; i != nact_; ++i)
        daxpy_(nbasis_, occup_[i], finact->element_ptr(0,nclosed_+i), 1, fact->data()+i*nbasis_, 1);
    }
    {
      // active Fock' operator (Fts+Fst) / (ns+nt)
      shared_ptr<QFile> ft(new QFile(nact_, nact_)); factp = ft;
      for (int i = 0; i != nact_; ++i)
        for (int j = 0; j != nact_; ++j)
          factp->element(j,i) = (fact->element(j+nclosed_,i)+fact->element(i+nclosed_,j)) / (occup_[i]+occup_[j]);
    }
    {
      // G matrix (active-active) 2Drs,tu Factp_tu - delta_rs nr sum_v Factp_vv
      shared_ptr<QFile> ft(new QFile(nact_, nact_)); gaa = ft;
      dgemv_("N", nact_*nact_, nact_*nact_, 1.0, fci_->rdm2_av()->data(), nact_*nact_, factp->data(), 1, 0.0, gaa->data(), 1);
      double p = 0.0;
      for (int i = 0; i != nact_; ++i) p += occup_[i] * factp->element(i,i);
      for (int i = 0; i != nact_; ++i) gaa->element(i,i) -= occup_[i] * p;
    }

    // first, <proj|H|0> is computed
    sigma_->zero();
    cc_->zero();
    cc_->ele_ref() = 1.0;

    // <a/i|H|0> = 2f_ai
    grad_vc(f, sigma_);
    // <a/r|H|0> = h_as d_sr + 2(as|tu)P_rs,tu = fact_rs
    grad_va(fact, sigma_);
    // <r/i|H|0> = 2f_ri - f^inact_is d_sr - 2(is|tu)P_rs,tu = 2f_ri - fact_ri
    grad_ca(f, fact, sigma_);
    sigma_->ele_ref() = 0.0;

    // setting error of macro iteration
    gradient = sigma_->ddot(*sigma_) / sigma_->size();

    // denominator
    shared_ptr<RotFile> denom_ = const_denom(gaa, factp, f);

    shared_ptr<RotFile> init_sigma(new RotFile(*sigma_));

    // ---------------------------------------
    // then microiteration for diagonalization
    // ---------------------------------------
    for (int miter = 0; miter != max_micro_iter_; ++miter) {

      if (miter != 0) {
        sigma_->zero();

        // equation 21d
        sigma_ai_ai_(cc_, sigma_, f);

        // equation 21e
        sigma_at_ai_(cc_, sigma_, fact);

        // equation 21f // note a typo!
        sigma_at_at_(cc_, sigma_, gaa, f);

        // equation 21b
        sigma_ai_ti_(cc_, sigma_, fact);

        // equation 21a
        sigma_ti_ti_(cc_, sigma_, gaa, f, factp);

        // projection to reference
        cc_->ele_ref()=0.0;
        sigma_->ele_ref() = init_sigma->ddot(*cc_);
      }

      // enters davidson iteration
      shared_ptr<RotFile> ccp(new RotFile(*cc_));
      shared_ptr<RotFile> sigmap(new RotFile(*sigma_));
      const double mic_energy = davidson.compute(ccp, sigmap);

      // residual vector and error
      shared_ptr<RotFile> residual = davidson.residual().front();
      const double error = residual->ddot(*residual) / residual->size();
#if 0
      cout << setw(3) << miter << "   " << setw(20) << setprecision(12) << mic_energy << " "
           << setw(10) << scientific << setprecision(2) << error << fixed << endl;
#endif

      if (error < thresh_micro_) break;

      // update cc_
      for (double *i = residual->begin(), *j = denom_->begin(); i != residual->end(); ++i, ++j) { *i /= *j; }
      const double a = davidson.orthog(residual);
      cc_ = residual;
    }
    // ---------------------------------------
    // micro iteration to here
    // ---------------------------------------


    // rotation parameters
    cc_ = davidson.civec().front();
    // unitary matrix
    shared_ptr<Matrix1e> rot = cc_->unpack(ref_->coeff()->geom())->exp();

    if (iter < diis_start_) {
      *ref_->coeff() *= *rot;
    } else {
      // including natorb.first to rot so that they can be processed at once
      shared_ptr<Matrix1e> tmp(new Matrix1e(*rot));
      dgemm_("N", "N", nact_, nbasis_, nact_, 1.0, &(natorb.first[0]), nact_, rot->element_ptr(nclosed_, 0), nbasis_, 0.0,
                                                                       tmp->element_ptr(nclosed_, 0), nbasis_);
      shared_ptr<Matrix1e> mcc = diis->extrapolate(tmp);
      shared_ptr<Coeff> newcc(new Coeff(*mcc));
      ref_->set_coeff(newcc);
    }

    // print out...
    int end = ::clock();
    if (nstate_ != 1 && iter) cout << endl;
    for (int i = 0; i != nstate_; ++i) {
      cout << indent << setw(5) << iter << setw(3) << i << setw(2) << (conv[i] ? "*" : " ")
                                        << setw(17) << fixed << setprecision(8) << energy[i] << "   "
                                        << setw(10) << scientific << setprecision(2) << (i==0 ? gradient : 0.0) << fixed << setw(10) << setprecision(2)
                                        << (end - start)/static_cast<double>(CLOCKS_PER_SEC) << endl;
    }

    if (*min_element(conv.begin(), conv.end())) break;
    if (iter == max_iter_-1) {
      cout << indent << endl << indent << "  * Max iteration reached in the CASSCF macro interation." << endl << endl;
      break;
    }
  }
  // ============================
  // macro iteration to here
  // ============================

}


shared_ptr<Coeff> SuperCI::update_coeff(const shared_ptr<Coeff> cold, vector<double> mat) const {
  shared_ptr<Matrix1e> cnew(new Matrix1e(*dynamic_cast<Matrix1e*>(cold.get())));
  int nbas = geom_->nbasis();
  dgemm_("N", "N", nbas, nact_, nact_, 1.0, cold->data()+nbas*nclosed_, nbas, &(mat[0]), nact_,
                   0.0, cnew->data()+nbas*nclosed_, nbas);
  shared_ptr<Coeff> cnew1(new Coeff(*cnew));
  return cnew1;
}


// <a/i|H|0> = 2f_ai
void SuperCI::grad_vc(const shared_ptr<Matrix1e> f, shared_ptr<RotFile> sigma) {
  if (!nvirt_ || !nclosed_) return;
  double* target = sigma->ptr_vc();
  for (int i = 0; i != nclosed_; ++i, target += nvirt_)
    daxpy_(nvirt_, 2.0, f->element_ptr(nocc_,i), 1, target, 1);
}


// <a/r|H|0> finact_as d_sr + 2(as|tu)P_rs,tu = fact_ar  (/nr)
void SuperCI::grad_va(const shared_ptr<QFile> fact, shared_ptr<RotFile> sigma) {
  if (!nvirt_ || !nact_) return;
  double* target = sigma->ptr_va();
  for (int i = 0; i != nact_; ++i, target += nvirt_) {
    daxpy_(nvirt_, 1.0/std::sqrt(occup_[i]), fact->element_ptr(nocc_, i), 1, target, 1);
  }
}


// <r/i|H|0> = (2f_ri - f^act_ri)/(2-nr)
void SuperCI::grad_ca(const shared_ptr<Matrix1e> f, shared_ptr<QFile> fact, shared_ptr<RotFile> sigma) {
  if (!nclosed_ || !nact_) return;
  double* target = sigma->ptr_ca();
  for (int i = 0; i != nact_; ++i, target += nclosed_) {
    daxpy_(nclosed_, 2.0/std::sqrt(2.0-occup_[i]), f->element_ptr(0,nclosed_+i), 1, target, 1);
    daxpy_(nclosed_, -1.0/std::sqrt(2.0-occup_[i]), fact->element_ptr(0,i), 1, target, 1);
  }
}


void SuperCI::compute_qxr(double* int1ext, shared_ptr<RDM<2> > rdm2, shared_ptr<QFile> qxr) {
  // int1ext = (xu|st) = (ts|ux), rdm2 = D_ru,st = D_ur,ts = D_ts,ur
  const int nbas = geom_->nbasis(); // caution :: this is AO and therefore not nbasis_
  const int common = nact_*nact_*nact_;
  double* buf = new double[nbas*nact_];
  dgemm_("T", "N", nbas, nact_, common, 1.0, int1ext, common, rdm2->first(), common, 0.0, buf, nbas);
  // slot in to an apropriate place
  dgemm_("T", "N", nbasis_, nact_, nbas, 1.0, ref_->coeff()->data(), nbas, buf, nbas, 0.0, qxr->data(), nbasis_);

  delete[] buf;
}


// sigma_at_at = delta_ab Gtu/sqrt(nt nu) + delta_tu Fab
void SuperCI::sigma_at_at_(const shared_ptr<RotFile> cc, shared_ptr<RotFile> sigma, const shared_ptr<QFile> gaa, const shared_ptr<Matrix1e> f) {
  if (!nact_ || !nvirt_) return;
  shared_ptr<QFile> gtup(new QFile(*gaa));
  for (int i = 0; i != nact_; ++i)
    for (int j = 0; j != nact_; ++j)
      gtup->element(j,i) /= std::sqrt(occup_[i]*occup_[j]);
  dgemm_("N", "N", nvirt_, nact_, nact_, 1.0, cc->ptr_va(), nvirt_, gtup->data(), nact_, 1.0, sigma->ptr_va(), nvirt_);
  dgemm_("N", "N", nvirt_, nact_, nvirt_, 1.0, f->element_ptr(nocc_, nocc_), nbasis_, cc->ptr_va(), nvirt_, 1.0, sigma->ptr_va(), nvirt_);
}


// sigma_ai_ai = delta_ij F_ab - delta_ab F_ij
void SuperCI::sigma_ai_ai_(const shared_ptr<RotFile> cc, shared_ptr<RotFile> sigma, const shared_ptr<Matrix1e> f) {
  if (!nact_ || !nvirt_) return;
  dgemm_("N", "N", nvirt_, nclosed_, nclosed_, -1.0, cc->ptr_vc(), nvirt_, f->data(), nbasis_, 1.0, sigma->ptr_vc(), nvirt_);
  dgemm_("N", "N", nvirt_, nclosed_, nvirt_, 1.0, f->element_ptr(nocc_, nocc_), nbasis_, cc->ptr_vc(), nvirt_, 1.0, sigma->ptr_vc(), nvirt_);
}


// sigma_at_ai = -delta_ab Fact_ti / sqrt(2nt)
void SuperCI::sigma_at_ai_(const shared_ptr<RotFile> cc, shared_ptr<RotFile> sigma, const shared_ptr<QFile> fact) {
  if (!nact_ || !nvirt_ || !nclosed_) return;
  QFile tmp(nclosed_, nact_);
  tmp.zero();
  for (int i = 0; i != nact_; ++i) {
    const double fac = -1.0 / std::sqrt(2.0*occup_[i]);
    daxpy_(nclosed_, fac, fact->element_ptr(0,i), 1, tmp.element_ptr(0,i), 1); 
  }
  dgemm_("N", "N", nvirt_, nact_, nclosed_, 1.0, cc->ptr_vc(), nvirt_, tmp.data(), nclosed_, 1.0, sigma->ptr_va(), nvirt_); 
  dgemm_("N", "T", nvirt_, nclosed_, nact_, 1.0, cc->ptr_va(), nvirt_, tmp.data(), nclosed_, 1.0, sigma->ptr_vc(), nvirt_); 
}


// sigma_ai_ti = sqrt((2-nt)/2) Fact_at
void SuperCI::sigma_ai_ti_(const shared_ptr<RotFile> cc, shared_ptr<RotFile> sigma, const shared_ptr<QFile> fact) {
  if (!nact_ || !nvirt_ || !nclosed_) return;
  QFile tmp(nvirt_, nact_);
  tmp.zero();
  for (int i = 0; i != nact_; ++i) {
    const double fac = std::sqrt(1.0-0.5*occup_[i]);
    daxpy_(nvirt_, fac, fact->element_ptr(nocc_,i), 1, tmp.element_ptr(0,i), 1); 
  }
  dgemm_("T", "N", nclosed_, nact_, nvirt_, 1.0, cc->ptr_vc(), nvirt_, tmp.data(), nvirt_, 1.0, sigma->ptr_ca(), nclosed_); 
  dgemm_("N", "T", nvirt_, nclosed_, nact_, 1.0, tmp.data(), nvirt_, cc->ptr_ca(), nclosed_, 1.0, sigma->ptr_vc(), nvirt_);

}


// sigma_ti_ti = delta_ij ((2-nt-nu)Fact_tu - G_tu)/sqrt((2-nt)(2-nu)) - delta_tu f_ij
void SuperCI::sigma_ti_ti_(const shared_ptr<RotFile> cc, shared_ptr<RotFile> sigma, const shared_ptr<QFile> gaa, const shared_ptr<Matrix1e> f,
                           const shared_ptr<QFile> factp) {
  if (!nact_ || !nclosed_) return;
  QFile tmp(nact_, nact_);
  for (int i = 0; i != nact_; ++i) {
    for (int j = 0; j != nact_; ++j) {
      tmp.element(j,i) = ((2.0 - occup_[j] - occup_[i]) * factp->element(j,i) - gaa->element(j,i))
                           / std::sqrt((2.0 - occup_[i]) * (2.0 - occup_[j]));
    }
  }
  dgemm_("N", "N", nclosed_, nact_, nact_, 1.0, cc->ptr_ca(), nclosed_, tmp.data(), nact_, 1.0, sigma->ptr_ca(), nclosed_); 
  dgemm_("N", "N", nclosed_, nact_, nclosed_, -1.0, f->data(), nbasis_, cc->ptr_ca(), nclosed_, 1.0, sigma->ptr_ca(), nclosed_); 
}


// compute denominators
shared_ptr<RotFile> SuperCI::const_denom(const shared_ptr<QFile> gaa, const shared_ptr<QFile> factp, const shared_ptr<Matrix1e> f) const {
  shared_ptr<RotFile> denom(new RotFile(nclosed_, nact_, nvirt_));
  fill(denom->data(), denom->data()+denom->size(), 1.0e100);

  double* target = denom->ptr_va();
  for (int i = 0; i != nact_; ++i)
    for (int j = 0; j != nvirt_; ++j, ++target)
      *target = gaa->element(i,i) / occup_[i] + f->element(j+nocc_, j+nocc_);

  target = denom->ptr_vc();
  for (int i = 0; i != nclosed_; ++i)
    for (int j = 0; j != nvirt_; ++j, ++target)
      *target = (f->element(j+nocc_, j+nocc_) - f->element(i, i));

  target = denom->ptr_ca();
  for (int i = 0; i != nact_; ++i) {
    const double fac = ((2.0 - 2.0*occup_[i]) * factp->element(i, i) - gaa->element(i, i)) / (2.0 - occup_[i]);
    for (int j = 0; j != nclosed_; ++j, ++target)
      *target = fac - f->element(j, j);
  }
  return denom;
}



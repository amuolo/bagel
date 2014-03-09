//
// Filename: matrix_interface.h
// Author: Ryan D. Reynolds <rreynoldschem@u.northwestern.edu>
//
// The contents of this file are used to interface MixedBasis with the complex London integral codes.
// It could conceivably be useful later on, but is intended as a crude patch to facilitate debugging.
//

#ifndef __SRC_INTEGRAL_COMPRYS_TEST_CODES_MATRIX_INTERFACE_H
#define __SRC_INTEGRAL_COMPRYS_TEST_CODES_MATRIX_INTERFACE_H

#include <cstdlib>
#include <type_traits>

namespace ryan {

template<typename Batch, typename DataType>
class RealLondon {
  protected:

    double* data_;
    std::shared_ptr<Batch> batch_;
    bool ReIm_;
    int nblocks_;
    int block_;
    int size_block_;

  public:
    RealLondon(const std::array<std::shared_ptr<const bagel::Shell>,2>& input, const bool ReIm, const int nblocks, const int block) {
      batch_ = std::make_shared<Batch>(input);
      ReIm_ = ReIm;
      nblocks_ = nblocks;
      block_ = block;
      if (block_ > nblocks_ || block_ < 1) throw std::runtime_error ("You're asking for a block of data that does not exist - ??");
      size_block_ = batch_->size_block();
    }

    double* data() {return data_;}

    void compute() {
      batch_->compute();
      const DataType* cdata = batch_->data();
      data_ = (double*) std::malloc(size_block_*sizeof(double));
      const int i = block_-1;
      if (std::is_same<DataType, double>::value) {
        for (int j=0; j!=size_block_; j++) {
          data_[j] = std::real(cdata[i*size_block_ + j]);
        }
      } else if (std::is_same<DataType, std::complex<double>>::value) {
        if (!ReIm_) {
          for (int j=0; j!=size_block_; j++) {
            data_[j] = std::real(cdata[i*size_block_ + j]);
          }
        } else {
          for (int j=0; j!=size_block_; j++) {
            data_[j] = std::imag(cdata[i*size_block_ + j]);
          }
        }
      } else throw std::runtime_error("data_ should be either double* or complex<double>*");
    }
};

std::complex<bagel::Matrix> transpose (std::complex<bagel::Matrix> S) {
  std::shared_ptr<bagel::Matrix> RT = S.real().transpose();
  std::shared_ptr<bagel::Matrix> IT = S.imag().transpose();
  std::complex<bagel::Matrix> out (*RT, *IT);
  return out;
}

std::complex<bagel::Matrix> scale (std::complex<double> c, std::complex<bagel::Matrix> A) {
  // Note: The accuracy of this function has not been checked!
  double a = c.real();
  double b = c.imag();
  bagel::Matrix Ra = A.real();
  bagel::Matrix Ia = A.imag();
  bagel::Matrix Rb = Ra;
  bagel::Matrix Ib = Ia;
  Ra.scale(a);
  Rb.scale(b);
  Ia.scale(a);
  Ib.scale(b);
  std::complex<bagel::Matrix> out ((Ra-Ib),(Rb+Ia));
  return out;
}

std::complex<bagel::Matrix> multiply (std::complex<bagel::Matrix> A, std::complex<bagel::Matrix> B) {
  bagel::Matrix real = A.real() * B.real() - A.imag() * B.imag();
  bagel::Matrix imag = A.real() * B.imag() + A.imag() * B.real();
  std::complex<bagel::Matrix> out (real, imag);
  return out;
}

std::complex<bagel::Matrix> multiply (std::complex<bagel::Matrix> A, std::complex<bagel::Matrix> B, std::complex<bagel::Matrix> C) {
  std::complex<bagel::Matrix> D = multiply (A, B);
  std::complex<bagel::Matrix> out = multiply (D, C);
  return out;
}

std::complex<bagel::Matrix> inverse (std::complex<bagel::Matrix> S) {
  bagel::Matrix S_Ri = S.real();
  S_Ri.inverse();
  bagel::Matrix Si_R = S.real() + (S.imag() * S_Ri * S.imag());
  Si_R.inverse();
  bagel::Matrix Si_I = S_Ri * S.imag() * Si_R;
  Si_I.scale(-1.0);
  std::complex<bagel::Matrix> out (Si_R, Si_I);
  return out;
}

double mean_unsigned_error (bagel::Matrix A, bagel::Matrix B, const bool rel) {
  assert (A.size() == B.size());
  const size_t size = A.size();
  const double* a = A.begin();
  const double* b = B.begin();
  double out = 0;
  if (rel) {
    for (int i=0; i!= size; i++) out += std::abs((a[i]-b[i])/a[i]);
  } else {
    for (int i=0; i!= size; i++) out += std::abs(a[i]-b[i]);
  }
  out /= size;
  return out;
}

double mean_unsigned_error (std::complex<bagel::Matrix> A, std::complex<bagel::Matrix> B, const bool rel) {
  assert (A.real().size() == B.real().size());
  assert (A.real().size() == B.imag().size());
  assert (A.real().size() == A.imag().size());
  const size_t size = A.real().size();

  bagel::Matrix Ar = A.real();
  bagel::Matrix Ai = A.imag();
  bagel::Matrix Br = B.real();
  bagel::Matrix Bi = B.imag();
  const double* ar = Ar.begin();
  const double* ai = Ai.begin();
  const double* br = Br.begin();
  const double* bi = Bi.begin();

  std::vector<std::complex<double>> a = {};
  std::vector<std::complex<double>> b = {};
  for (int i=0; i!=size; i++) {
    std::complex<double> an (ar[i],ai[i]);
    std::complex<double> bn (br[i],bi[i]);
    a.push_back(an);
    b.push_back(bn);
  }

  double out = 0;
  if (rel) {
    for (int i=0; i!= size; i++) out += std::abs((a[i]-b[i])/a[i]);
  } else {
    for (int i=0; i!= size; i++) out += std::abs(a[i]-b[i]);
  }
  out /= size;
  return out;
}

}

#endif

//
// BAGEL - Parallel electron correlation program.
// Filename: reldfhalf.cc
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//


#include <src/rel/reldfhalf.h>

using namespace std;
using namespace bagel;

RelDFHalf::RelDFHalf(shared_ptr<const RelDF> df, std::vector<shared_ptr<const SpinorInfo>> bas, array<shared_ptr<const Matrix>,4> rcoeff, array<shared_ptr<const Matrix>,4> icoeff)
: RelDFBase(*df) {

  basis_ = bas;

  const int index = basis_.front()->basis(0);
  for (auto& i : basis_)
    if (i->basis(0) != index) throw logic_error("basis should have the same first index");
  // -1 due to dagger
  auto icoeff_scaled = make_shared<const Matrix>(*icoeff[index] * (-1.0));

  if (df->swapped()) {
    dfhalf_[0] = df->df()->compute_half_transform_swap(rcoeff[index]);
    dfhalf_[1] = df->df()->compute_half_transform_swap(icoeff_scaled);
  } else {
    dfhalf_[0] = df->df()->compute_half_transform(rcoeff[index]);
    dfhalf_[1] = df->df()->compute_half_transform(icoeff_scaled);
  }
}


RelDFHalf::RelDFHalf(shared_ptr<const RelDF_London> df, std::vector<shared_ptr<const SpinorInfo>> bas, array<shared_ptr<const Matrix>,4> rcoeff, array<shared_ptr<const Matrix>,4> icoeff)
: RelDFBase(*df) {

  basis_ = bas;

  const int index = basis_.front()->basis(0);
  for (auto& i : basis_)
    if (i->basis(0) != index) throw logic_error("basis should have the same first index");
  // -1 due to dagger (We are transforming the bra.)
  auto icoeff_scaled = make_shared<const Matrix>(*icoeff[index] * (-1.0));
  auto ricoeff = make_shared<const Matrix>(*rcoeff[index] + *icoeff_scaled);

  // df->get_real() +/- df->get_imag() needed for 3-multiplication algorithm
  auto dfri = make_shared<DFDist>(df->get_imag());
  const int n = df->get_real()->block().size();
  const double scale = df->swapped() ? -1.0 : 1.0;
  for (int i=0; i!=n; ++i) {
    dfri->add_block(df->get_real()->block(i)->copy());
    dfri->block(i)->ax_plus_y(scale, df->get_imag()->block(i));
  }

  if (df->swapped()) {
    dfhalf_[0] = df->get_real()->compute_half_transform_swap(rcoeff[index]);
    auto tmp = df->get_imag()->compute_half_transform_swap(icoeff_scaled);
    dfhalf_[1] = dfri->compute_half_transform_swap(ricoeff);

    dfhalf_[1]->ax_plus_y(-1.0, dfhalf_[0]);
    dfhalf_[1]->ax_plus_y( 1.0, tmp);
    dfhalf_[0]->ax_plus_y( 1.0, tmp);
  } else {
    dfhalf_[0] = df->get_real()->compute_half_transform(rcoeff[index]);
    auto tmp = df->get_imag()->compute_half_transform(icoeff_scaled);
    dfhalf_[1] = dfri->compute_half_transform(ricoeff);

    dfhalf_[1]->ax_plus_y(-1.0, dfhalf_[0]);
    dfhalf_[1]->ax_plus_y(-1.0, tmp);
    dfhalf_[0]->ax_plus_y(-1.0, tmp);
  }
}



RelDFHalf::RelDFHalf(array<shared_ptr<DFHalfDist>,2> data, pair<int, int> cartesian, vector<shared_ptr<const SpinorInfo>> bas) : RelDFBase(cartesian), dfhalf_(data) {
  basis_ = bas;
}


RelDFHalf::RelDFHalf(const RelDFHalf& o) : RelDFBase(o.cartesian_) {
  basis_ = o.basis_;
  dfhalf_[0] = o.dfhalf_[0]->copy();
  dfhalf_[1] = o.dfhalf_[1]->copy();
}


shared_ptr<RelDFHalf> RelDFHalf::apply_J() const {
  return make_shared<RelDFHalf>(array<shared_ptr<DFHalfDist>,2>{{dfhalf_[0]->apply_J(), dfhalf_[1]->apply_J()}}, cartesian_, basis_);
}


shared_ptr<RelDFHalf> RelDFHalf::apply_JJ() const {
  return make_shared<RelDFHalf>(array<shared_ptr<DFHalfDist>,2>{{dfhalf_[0]->apply_JJ(), dfhalf_[1]->apply_JJ()}}, cartesian_, basis_);
}


void RelDFHalf::set_sum_diff() {
  df2_[0] = dfhalf_[0]->copy();
  df2_[0]->ax_plus_y(1.0, dfhalf_[1]);
  df2_[1] = dfhalf_[0]->copy();
  df2_[1]->ax_plus_y(-1.0, dfhalf_[1]);
}


void RelDFHalf::ax_plus_y(std::complex<double> a, std::shared_ptr<const RelDFHalf> o) {
  if (imag(a) == 0.0) {
    const double fac = real(a);
    dfhalf_[0]->ax_plus_y(fac, o->dfhalf_[0]);
    dfhalf_[1]->ax_plus_y(fac, o->dfhalf_[1]);
  } else if (real(a) == 0.0) {
    const double fac = imag(a);
    dfhalf_[0]->ax_plus_y(-fac, o->dfhalf_[1]);
    dfhalf_[1]->ax_plus_y( fac, o->dfhalf_[0]);
  } else {
    const double rfac = real(a);
    dfhalf_[0]->ax_plus_y(rfac, o->dfhalf_[0]);
    dfhalf_[1]->ax_plus_y(rfac, o->dfhalf_[1]);
    const double ifac = imag(a);
    dfhalf_[0]->ax_plus_y(-ifac, o->dfhalf_[1]);
    dfhalf_[1]->ax_plus_y( ifac, o->dfhalf_[0]);
  }
}


bool RelDFHalf::matches(shared_ptr<const RelDFHalf> o) const {
  return cartesian_.second == o->cartesian().second && basis_[0]->basis(1) == o->basis_[0]->basis(1) && alpha_matches(o);
}


bool RelDFHalf::alpha_matches(shared_ptr<const Breit2Index> o) const {
  assert(basis_.size() == 1);
  return basis_[0]->alpha_comp() == o->index().second;
}


bool RelDFHalf::alpha_matches(shared_ptr<const RelDFHalf> o) const {
  assert(basis_.size() == 1);
  return basis_[0]->alpha_comp() == o->basis()[0]->alpha_comp();
}


// assumes you are multiplying breit2index by 2nd integral, not first (see alpha_matches)
shared_ptr<RelDFHalf> RelDFHalf::multiply_breit2index(shared_ptr<const Breit2Index> bt) const {
  assert(basis_.size() == 1);
  array<shared_ptr<DFHalfDist>,2> d = {{ dfhalf_[0]->apply_J(bt->data()), dfhalf_[1]->apply_J(bt->data())}};

  vector<shared_ptr<const SpinorInfo>> spinor = { make_shared<const SpinorInfo>(basis_[0]->basis(), bt->index().first, bt->index().second) };
  return make_shared<RelDFHalf>(d, cartesian_, spinor);
}


list<shared_ptr<RelDFHalf>> RelDFHalf::split(const bool docopy) {
  list<shared_ptr<RelDFHalf>> out;
  for (auto i = basis().begin(); i != basis().end(); ++i) {
    if (i == basis().begin() && docopy) {
      out.push_back(make_shared<RelDFHalf>(dfhalf_, cartesian_, vector<std::shared_ptr<const SpinorInfo>>{*i}));
    } else {
      // TODO Any way to avoid copying?
      array<shared_ptr<DFHalfDist>,2> d = {{ dfhalf_[0]->copy(), dfhalf_[1]->copy() }};
      out.push_back(make_shared<RelDFHalf>(d, cartesian_, vector<std::shared_ptr<const SpinorInfo>>{*i}));
    }
  }
  return out;
}


shared_ptr<DFDist> RelDFHalfB::back_transform(shared_ptr<const Matrix> r, shared_ptr<const Matrix> i, const bool imag) const {
  shared_ptr<DFDist> out;
  if (!imag) {
    out = dfhalf_[0]->back_transform(r);
    out->ax_plus_y(-1.0, dfhalf_[1]->back_transform(i));
  } else {
    out = dfhalf_[0]->back_transform(i);
    out->ax_plus_y(1.0, dfhalf_[1]->back_transform(r));
  }
  return out;
}

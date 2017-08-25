//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: goverlap.cc
// Copyright (C) 2017 Toru Shiozaki
//
// Author: Nils Strand <nilsstrand2022@u.northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#include <src/mat1e/grad/goverlap.h>
#include <src/integral/os/goverlapbatch.h>

using namespace std;
using namespace bagel;

BOOST_CLASS_EXPORT_IMPLEMENT(GOverlap)

GOverlap::GOverlap(shared_ptr<const Molecule> mol) : Matrix1e(mol) {

  init(mol);
  fill_upper();

}


void GOverlap::computebatch(const array<shared_ptr<const Shell>,2>& input, const int offsetb0, const int offsetb1, shared_ptr<const Molecule>) {

  // input = [b1, b0]
  assert(input.size() == 2);
  const int dimb1 = input[0]->nbasis();
  const int dimb0 = input[1]->nbasis();
  GOverlapBatch overlap(input);
  overlap.compute();

  copy_block(offsetb1, offsetb0, dimb1, dimb0, overlap.data());
}

//
// BAGEL - Parallel electron correlation program.
// Filename: _sphusp_4.cc
// Copyright (C) 2014 Toru Shiozaki
//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
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

#include <algorithm>
#include <cassert>
#include <src/integral/ecp/sphusplist.h>

using namespace std;
using namespace bagel;

vector<double> SphUSPList::sphusp_4(const int m) {

  vector<double> c;
  constexpr double coeff[135] = {   0.000000000000000e+00,   2.503342941796705e+00,   0.000000000000000e+00,  -2.503342941796705e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   5.310392309339792e+00,   0.000000000000000e+00,  -1.770130769779931e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,  -9.461746957575600e-01,   0.000000000000000e+00,  -9.461746957575600e-01,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   5.677048174545360e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,  -2.007139630671867e+00,   0.000000000000000e+00,  -2.007139630671867e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   2.676186174229156e+00,   0.000000000000000e+00,
   3.173566407456129e-01,   0.000000000000000e+00,   6.347132814912257e-01,   0.000000000000000e+00,   3.173566407456129e-01,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,  -2.538853125964903e+00,
   0.000000000000000e+00,  -2.538853125964903e+00,   0.000000000000000e+00,   0.000000000000000e+00,   8.462843753216343e-01,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
  -2.007139630671867e+00,   0.000000000000000e+00,  -2.007139630671867e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   2.676186174229156e+00,   0.000000000000000e+00,   0.000000000000000e+00,
  -4.730873478787800e-01,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   4.730873478787800e-01,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   2.838524087272680e+00,
   0.000000000000000e+00,  -2.838524087272680e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   1.770130769779931e+00,   0.000000000000000e+00,  -5.310392309339792e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   6.258357354491763e-01,   0.000000000000000e+00,  -3.755014412695058e+00,   0.000000000000000e+00,   6.258357354491763e-01,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,
   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00
};

  assert(abs(m) <= 4);
  const int size_c = (4 + 1) * (4 + 2) / 2;
  const int mu = m + 4;
  const int i0 = mu * size_c;
  for (int i = i0; i != i0 + size_c; ++i) c.push_back(coeff[i]);
  return c;

}

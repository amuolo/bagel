//
// BAGEL - Parallel electron correlation program.
// Filename: meh_ras_sigma.cc
// Copyright (C) 2013 Toru Shiozaki
//
// Author: Shane Parker <shane.parker@u.northwestern.edu>
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

#include <src/meh/meh_ras.h>
#include <src/ras/form_sigma.h>

using namespace std;
using namespace bagel;

MEH_RAS::MEH_RAS(const shared_ptr<const PTree> input, shared_ptr<Dimer> dimer, shared_ptr<DimerRAS> cispace) :
  MultiExcitonHamiltonian<RASDvec>(input, dimer, cispace)
{
  sparse_ = input->get<bool>("sparse", true);
}


shared_ptr<RASDvec> MEH_RAS::form_sigma(shared_ptr<const RASDvec> ccvec, const double* h1, const double* mo2e_ptr) const {
  FormSigmaRAS form(sparse_);
  return form(ccvec, h1, mo2e_ptr);
}

shared_ptr<RASDvec> MEH_RAS::form_sigma_1e(shared_ptr<const RASDvec> ccvec, const double* modata) const {
  FormSigmaRAS form(sparse_);
  return form(ccvec, modata);
}
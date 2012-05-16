//
// Newint - Parallel electron correlation program.
// Filename: uhf.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the Newint package (to be renamed).
//
// The Newint package is free software; you can redistribute it and\/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// The Newint package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the Newint package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//


#ifndef __NEWINT_SRC_SCF_UHF_H
#define __NEWINT_SRC_SCF_UHF_H

#include <src/scf/scf_base.h>
#include <src/util/diis.h>

// I only implement a DF version
//template<int DF>

class UHF : public SCF_base {
  protected:
    std::shared_ptr<Matrix1e> aodensityA_;
    std::shared_ptr<Matrix1e> aodensityB_;
    std::shared_ptr<Coeff> coeffB_;

    std::unique_ptr<double[]> eigB_;
    double* eigB() { return eigB_.get(); };

    void print_S2(const std::string) const;

  public:
    UHF(std::multimap<std::string, std::string>& idata_, const std::shared_ptr<const Geometry> geom)
      : SCF_base(idata_, geom) {
      // TODO init schwarz for auxiliary basis
    };

    ~UHF() {};

    std::tuple<std::shared_ptr<Matrix1e>,std::shared_ptr<Matrix1e>, std::shared_ptr<Matrix1e> > form_density_uhf() const;

    virtual void compute();

    std::shared_ptr<Reference> conv_to_ref() const;
    // return the natural orbital coefficients and nclosed and nact
    std::tuple<std::shared_ptr<Coeff>, int, std::vector<std::shared_ptr<RDM<1> > > > natural_orbitals() const;
};

#endif

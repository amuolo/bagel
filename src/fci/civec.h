//
// BAGEL - Parallel electron correlation program.
// Filename: civec.h
// Copyright (C) 2011 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and\/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
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


#ifndef NEWINT_FCI_CIVEC_H
#define NEWINT_FCI_CIVEC_H

#include <stddef.h>
#include <list>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <src/parallel/staticdist.h>
#include <src/util/f77.h>
#include <src/fci/determinants.h>
#include <src/parallel/request.h>

namespace bagel {

class DistCivec;

class Civec {
  protected:
    // The determinant space in which this Civec object is defined
    mutable std::shared_ptr<const Determinants> det_;

    size_t lena_;
    size_t lenb_;

    // !!CAUTION!!
    // cc is formated so that B runs first.
    // Also, cc_ can be null if this is constructed by Dvec.
    std::unique_ptr<double[]> cc_;

    double* cc_ptr_;

    double& cc(const size_t& i) { return *(cc_ptr_+i); }
    const double& cc(const size_t& i) const { return *(cc_ptr_+i); }
    double* cc() { return cc_ptr_; }
    const double* cc() const { return cc_ptr_; }

  public:
    Civec(std::shared_ptr<const Determinants> det);

    // constructor that is called by Dvec.
    Civec(std::shared_ptr<const Determinants> det, double* din_);

    // copy constructor
    Civec(const Civec& o);
    // from a distribtued Civec
    Civec(const DistCivec& o);

    // this is not a copy constructor.
    Civec(std::shared_ptr<Civec> o, std::shared_ptr<const Determinants> det);

    double* data() { return cc(); }
    double& element(size_t i, size_t j) { return cc(i+j*lenb_); }
    double* element_ptr(size_t i, size_t j) { return cc()+i+j*lenb_; }

    double& data(const size_t& i) { return cc(i); }
    const double& data(const size_t& i) const { return cc(i); }

    const double* data() const { return cc(); }
    const double* element_ptr(size_t i, size_t j) const { return cc()+i+j*lenb_; }

    std::shared_ptr<const Determinants> det() const { return det_; }
    void set_det(std::shared_ptr<const Determinants> o) const { det_ = o; }

    void zero() { std::fill(cc(), cc()+lena_*lenb_, 0.0); }

    size_t size() const { return lena_*lenb_; }

    std::shared_ptr<Civec> transpose() const;

    size_t lena() const { return lena_; }
    size_t lenb() const { return lenb_; }

    // some functions for convenience
    void daxpy(double a, const Civec& other);
    double ddot(const Civec& other) const;
    double norm() const;
    double variance() const;
    void scale(const double a);

    Civec& operator*=(const double& a) { scale(a); return *this; }
    Civec& operator+=(const double& a) { daxpy_(size(),  1.0, &a, 0, data(), 1); return *this; }
    Civec& operator-=(const double& a) { daxpy_(size(), -1.0, &a, 0, data(), 1); return *this; }

    Civec& operator=(const Civec& o) { assert(size() == o.size()); std::copy(o.cc(), o.cc()+size(), cc()); return *this; }
    Civec& operator+=(const Civec& o) { daxpy( 1.0, o); return *this; }
    Civec& operator-=(const Civec& o) { daxpy(-1.0, o); return *this; }
    Civec& operator/=(const Civec& o);
    Civec operator/(const Civec& o) const;

    // assumes that Civec's in c are already orthogonal with each other.
    // returns scaling factor (see implementation)

    double orthog(std::list<std::shared_ptr<const Civec> > c);
    double orthog(std::shared_ptr<const Civec> o);
    void project_out(std::shared_ptr<const Civec> o) { daxpy(-ddot(*o), *o); }

    void print(const double thresh) const { det_->print(data(), thresh); }

    std::shared_ptr<DistCivec> distcivec() const;
};


class DistCivec {
  protected:
    // for compatibility with Civec
    mutable std::shared_ptr<const Determinants> det_;

    // global dimension
    size_t lena_;
    size_t lenb_;

    // local storage
    std::unique_ptr<double[]> local_;

    // local alpha strings
    size_t astart_;
    size_t aend_;

    // allocation size
    size_t alloc_;

    // tag for MPI_Win
    mutable int win_;

    // table for alpha string distribution
    const StaticDist dist_;

    // MPI send/receive management
    std::shared_ptr<AccRequest> accum_;
    std::shared_ptr<SendRequest> send_;

  public:
    DistCivec(std::shared_ptr<const Determinants> det);

    double& local(const size_t i) { return local_[i]; }
    const double& local(const size_t i) const { return local_[i]; }

    double* local() { return local_.get(); } 
    const double* local() const { return local_.get(); } 

    size_t size() const { return lena_*(aend_-astart_); }
    size_t global_size() const { return lena_*lenb_; }
    size_t lena() const { return lena_; }
    size_t lenb() const { return lenb_; }

    size_t astart() const { return astart_; }
    size_t aend() const { return aend_; }
    size_t asize() const { return aend_ - astart_; }

    void zero() { std::fill_n(local_.get(), size(), 0.0); }

    std::shared_ptr<Civec> civec() const { return std::shared_ptr<Civec>(new Civec(*this)); }
    std::shared_ptr<const Determinants> det() const { return det_; }

    std::shared_ptr<DistCivec> clone() const { return std::shared_ptr<DistCivec>(new DistCivec(det_)); }

    // MPI Window creation/annihilation for one-sided communication
    void open_window() const;
    void close_window() const;
    void fence() const;
    void get_bstring(double* buf, const size_t a) const; 
    void put_bstring(const double* buf, const size_t a) const; 
    void accumulate_bstring(const double* buf, const size_t a) const; 

    // MPI Isend Irecv
    void init_accumulate_buf(const size_t cmm);
    void accumulate_bstring_buf(std::unique_ptr<double[]>& buf, const size_t a) const; 
    void flush() const;
    void wait() const;

};

}

#endif

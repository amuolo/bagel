//
// BAGEL - Parallel electron correlation program.
// Filename: RelMRCI_tasks19.cc
// Copyright (C) 2014 Shiozaki group
//
// Author: Shiozaki group <shiozaki@northwestern.edu>
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

#include <bagel_config.h>
#ifdef COMPILE_SMITH

#include <src/smith/RelMRCI_tasks19.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::RelMRCI;

void Task900::Task_local::compute() {
  const Index c3 = b(0);
  const Index x5 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: I1660
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x5, x0, x1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x5, x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x5, x0, x1), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma534
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x0, x4, x1, x3, x2);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x0, x4, x1, x3, x2)]);
        sort_indices<2,4,5,0,1,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x1.size(), x3.size(), x2.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, c3, x3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, c3, x3, x2)]);
        sort_indices<0,2,3,1,0,1,-1,2>(i1data, i1data_sorted, x4.size(), c3.size(), x3.size(), x2.size());
        zgemm3m_("T", "N", x5.size()*x0.size()*x1.size(), c3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x0.size()*x1.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x0.size(), x1.size(), c3.size());
  out()->put_block(odata, c3, x5, x0, x1);
}

void Task901::Task_local::compute() {
  const Index c3 = b(0);
  const Index x5 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: I1660
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x5, x0, x1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x5, x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x5, x0, x1), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma54
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x0, x4, x3, x2, x1);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x0, x4, x3, x2, x1)]);
        sort_indices<2,3,4,0,1,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x3.size(), x2.size(), x1.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, x3, x2, c3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, x3, x2, c3)]);
        sort_indices<0,1,2,3,0,1,-1,2>(i1data, i1data_sorted, x4.size(), x3.size(), x2.size(), c3.size());
        zgemm3m_("T", "N", x5.size()*x0.size()*x1.size(), c3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x0.size()*x1.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x0.size(), x1.size(), c3.size());
  out()->put_block(odata, c3, x5, x0, x1);
}

void Task902::Task_local::compute() {
  const Index a1 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index a2 = b(3);
  // tensor label: I247
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a1, x0, x1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a1, x0, x1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, x0, x1, a2), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma511
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, x1, x2, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, x1, x2, x0)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x1.size(), x2.size(), x0.size());
      // tensor label: I1666
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x2, a2, x3, a1);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x2, a2, x3, a1)]);
      sort_indices<2,0,1,3,0,1,1,1>(i1data, i1data_sorted, x2.size(), a2.size(), x3.size(), a1.size());
      zgemm3m_("T", "N", x1.size()*x0.size(), a2.size()*a1.size(), x2.size()*x3.size(),
             1.0, i0data_sorted, x2.size()*x3.size(), i1data_sorted, x2.size()*x3.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<3,1,0,2,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), a1.size());
  out()->put_block(odata, a1, x0, x1, a2);
}

void Task903::Task_local::compute() {
  const Index x2 = b(0);
  const Index a2 = b(1);
  const Index x3 = b(2);
  const Index a1 = b(3);
  // tensor label: I1666
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x2, a2, x3, a1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x2, a2, x3, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, a2, x3, a1), 0.0);
  for (auto& a3 : *range_[2]) {
    for (auto& c4 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, a3, c4, a1);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, a3, c4, a1)]);
      sort_indices<1,2,0,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a3.size(), c4.size(), a1.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x2, c4, a3, a2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x2, c4, a3, a2)]);
      sort_indices<2,1,0,3,0,1,1,1>(i1data, i1data_sorted, x2.size(), c4.size(), a3.size(), a2.size());
      zgemm3m_("T", "N", x3.size()*a1.size(), x2.size()*a2.size(), c4.size()*a3.size(),
             1.0, i0data_sorted, c4.size()*a3.size(), i1data_sorted, c4.size()*a3.size(),
             1.0, odata_sorted, x3.size()*a1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x3.size(), a1.size(), x2.size(), a2.size());
  out()->put_block(odata, x2, a2, x3, a1);
}

void Task904::Task_local::compute() {
  const Index a1 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index a2 = b(3);
  // tensor label: I247
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a1, x0, x1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a1, x0, x1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, x0, x1, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        for (auto& x2 : *range_[1]) {
          // tensor label: Gamma534
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x0, x4, x1, x3, x2);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x0, x4, x1, x3, x2)]);
          sort_indices<0,2,4,5,1,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x1.size(), x3.size(), x2.size());
          // tensor label: I1678
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a2, x3, x2, x5, a1, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a2, x3, x2, x5, a1, x4)]);
          sort_indices<3,5,1,2,0,4,0,1,1,1>(i1data, i1data_sorted, a2.size(), x3.size(), x2.size(), x5.size(), a1.size(), x4.size());
          zgemm3m_("T", "N", x0.size()*x1.size(), a2.size()*a1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x0.size()*x1.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a2.size(), a1.size());
  out()->put_block(odata, a1, x0, x1, a2);
}

void Task905::Task_local::compute() {
  const Index a2 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x5 = b(3);
  const Index a1 = b(4);
  const Index x4 = b(5);
  // tensor label: I1678
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a2, x3, x2, x5, a1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a2, x3, x2, x5, a1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, x3, x2, x5, a1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a1, x4, a3);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a1, x4, a3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a1.size(), x4.size(), a3.size());
    // tensor label: I1679
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, a2, x3, x2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, a2, x3, x2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), a2.size(), x3.size(), x2.size());
    zgemm3m_("T", "N", x5.size()*a1.size()*x4.size(), a2.size()*x3.size()*x2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, x5.size()*a1.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), a1.size(), x4.size(), a2.size(), x3.size(), x2.size());
  out()->put_block(odata, a2, x3, x2, x5, a1, x4);
}

void Task906::Task_local::compute() {
  const Index a3 = b(0);
  const Index a2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I1679
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, a2, x3, x2);
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(a3, a2, x3, x2);
    sort_indices<0,1,2,3,1,1,1,1>(i0data, odata, a3.size(), a2.size(), x3.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(x3, x2, a3, a2);
    sort_indices<2,3,0,1,1,1,1,1>(i1data, odata, x3.size(), x2.size(), a3.size(), a2.size());
  }
  out()->put_block(odata, a3, a2, x3, x2);
}

void Task907::Task_local::compute() {
  const Index a1 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index a2 = b(3);
  // tensor label: I247
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a1, x0, x1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a1, x0, x1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, x0, x1, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        for (auto& x2 : *range_[1]) {
          // tensor label: Gamma54
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x0, x4, x3, x2, x1);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x0, x4, x3, x2, x1)]);
          sort_indices<0,2,3,4,1,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x3.size(), x2.size(), x1.size());
          // tensor label: I1681
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, x2, a2, x5, a1, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, x2, a2, x5, a1, x4)]);
          sort_indices<3,5,0,1,2,4,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), a2.size(), x5.size(), a1.size(), x4.size());
          zgemm3m_("T", "N", x0.size()*x1.size(), a2.size()*a1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x0.size()*x1.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a2.size(), a1.size());
  out()->put_block(odata, a1, x0, x1, a2);
}

void Task908::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index a2 = b(2);
  const Index x5 = b(3);
  const Index a1 = b(4);
  const Index x4 = b(5);
  // tensor label: I1681
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x3, x2, a2, x5, a1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x3, x2, a2, x5, a1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2, a2, x5, a1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a1, x4, a3);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a1, x4, a3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a1.size(), x4.size(), a3.size());
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x3, x2, a2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x3, x2, a2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), x3.size(), x2.size(), a2.size());
    zgemm3m_("T", "N", x5.size()*a1.size()*x4.size(), x3.size()*x2.size()*a2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, x5.size()*a1.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), a1.size(), x4.size(), x3.size(), x2.size(), a2.size());
  out()->put_block(odata, x3, x2, a2, x5, a1, x4);
}

void Task909::Task_local::compute() {
  const Index a1 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index a2 = b(3);
  // tensor label: I247
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a1, x0, x1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a1, x0, x1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, x0, x1, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        for (auto& x3 : *range_[1]) {
          // tensor label: Gamma553
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x0, x4, x2, x3, x1);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x0, x4, x2, x3, x1)]);
          sort_indices<0,2,3,4,1,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x2.size(), x3.size(), x1.size());
          // tensor label: I1684
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, a2, x2, x5, a1, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, a2, x2, x5, a1, x4)]);
          sort_indices<3,5,2,0,1,4,0,1,1,1>(i1data, i1data_sorted, x3.size(), a2.size(), x2.size(), x5.size(), a1.size(), x4.size());
          zgemm3m_("T", "N", x0.size()*x1.size(), a2.size()*a1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x0.size()*x1.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a2.size(), a1.size());
  out()->put_block(odata, a1, x0, x1, a2);
}

void Task910::Task_local::compute() {
  const Index x3 = b(0);
  const Index a2 = b(1);
  const Index x2 = b(2);
  const Index x5 = b(3);
  const Index a1 = b(4);
  const Index x4 = b(5);
  // tensor label: I1684
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x3, a2, x2, x5, a1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x3, a2, x2, x5, a1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, a2, x2, x5, a1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a1, x4, a3);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a1, x4, a3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a1.size(), x4.size(), a3.size());
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, a2, a3, x2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, a2, a3, x2)]);
    sort_indices<2,0,1,3,0,1,-1,1>(i1data, i1data_sorted, x3.size(), a2.size(), a3.size(), x2.size());
    zgemm3m_("T", "N", x5.size()*a1.size()*x4.size(), x3.size()*a2.size()*x2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, x5.size()*a1.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), a1.size(), x4.size(), x3.size(), a2.size(), x2.size());
  out()->put_block(odata, x3, a2, x2, x5, a1, x4);
}

void Task911::Task_local::compute() {
  const Index c2 = b(0);
  const Index x1 = b(1);
  const Index c1 = b(2);
  const Index x0 = b(3);
  // tensor label: r
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c2, x1, c1, x0);
  {
    // tensor label: I268
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, c2, x1, x0);
    sort_indices<1,2,0,3,1,1,1,1>(i0data, odata, c1.size(), c2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, c2, x1, c1, x0);
}

void Task912::Task_local::compute() {
  const Index c1 = b(0);
  const Index c2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I268
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c2, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x1, x3, x0, x2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x1, x3, x0, x2)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x1.size(), x3.size(), x0.size(), x2.size());
      // tensor label: I269
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c2, x3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c2, x3, x2)]);
      sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, c1.size(), c2.size(), x3.size(), x2.size());
      zgemm3m_("T", "N", x1.size()*x0.size(), c1.size()*c2.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), c1.size(), c2.size());
  out()->put_block(odata, c1, c2, x1, x0);
}

void Task913::Task_local::compute() {
  const Index c1 = b(0);
  const Index c2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I269
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c2, x3, x2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c2, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c2, x3, x2), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& c4 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c3, x3, c4, x2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c3, x3, c4, x2)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, c3.size(), x3.size(), c4.size(), x2.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c4, c2, c3);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c4, c2, c3)]);
      sort_indices<3,1,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), c4.size(), c2.size(), c3.size());
      zgemm3m_("T", "N", x3.size()*x2.size(), c1.size()*c2.size(), c4.size()*c3.size(),
             1.0, i0data_sorted, c4.size()*c3.size(), i1data_sorted, c4.size()*c3.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), c1.size(), c2.size());
  out()->put_block(odata, c1, c2, x3, x2);
}

void Task914::Task_local::compute() {
  const Index c1 = b(0);
  const Index c2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I269
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c2, x3, x2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c2, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c2, x3, x2), 0.0);
  for (auto& a3 : *range_[2]) {
    for (auto& a4 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a3, c2, a4);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a3, c2, a4)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a3.size(), c2.size(), a4.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a4, x3, a3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a4, x3, a3, x2)]);
      sort_indices<2,0,1,3,0,1,-2,1>(i1data, i1data_sorted, a4.size(), x3.size(), a3.size(), x2.size());
      zgemm3m_("T", "N", c1.size()*c2.size(), x3.size()*x2.size(), a4.size()*a3.size(),
             1.0, i0data_sorted, a4.size()*a3.size(), i1data_sorted, a4.size()*a3.size(),
             1.0, odata_sorted, c1.size()*c2.size());
    }
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, c1.size(), c2.size(), x3.size(), x2.size());
  out()->put_block(odata, c1, c2, x3, x2);
}

void Task915::Task_local::compute() {
  const Index c1 = b(0);
  const Index c2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I268
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c2, x1, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      // tensor label: Gamma556
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x0, x5, x1, x4);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x0, x5, x1, x4)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x0.size(), x5.size(), x1.size(), x4.size());
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x5, c2, x4);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x5, c2, x4)]);
      sort_indices<1,3,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), x5.size(), c2.size(), x4.size());
      zgemm3m_("T", "N", x0.size()*x1.size(), c1.size()*c2.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<2,3,1,0,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), c1.size(), c2.size());
  out()->put_block(odata, c1, c2, x1, x0);
}

void Task916::Task_local::compute() {
  const Index c1 = b(0);
  const Index c2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I268
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c2, x1, x0), 0.0);
  for (auto& x7 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      // tensor label: Gamma557
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x0, x7, x1, x6);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x0, x7, x1, x6)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x0.size(), x7.size(), x1.size(), x6.size());
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x7, c2, x6);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x7, c2, x6)]);
      sort_indices<1,3,0,2,0,1,-1,1>(i1data, i1data_sorted, c1.size(), x7.size(), c2.size(), x6.size());
      zgemm3m_("T", "N", x0.size()*x1.size(), c1.size()*c2.size(), x7.size()*x6.size(),
             1.0, i0data_sorted, x7.size()*x6.size(), i1data_sorted, x7.size()*x6.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<2,3,1,0,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), c1.size(), c2.size());
  out()->put_block(odata, c1, c2, x1, x0);
}

void Task917::Task_local::compute() {
  const Index c3 = b(0);
  const Index a4 = b(1);
  const Index c1 = b(2);
  const Index a2 = b(3);
  // tensor label: r
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, a4, c1, a2);
  {
    // tensor label: I1128
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, c3, a2, a4);
    sort_indices<1,3,0,2,1,1,1,1>(i0data, odata, c1.size(), c3.size(), a2.size(), a4.size());
  }
  out()->put_block(odata, c3, a4, c1, a2);
}

void Task918::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x0 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x1, a2, x0, a4);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x1, a2, x0, a4)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x1.size(), a2.size(), x0.size(), a4.size());
      // tensor label: I1129
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x1, x0)]);
      sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", a2.size()*a4.size(), c1.size()*c3.size(), x1.size()*x0.size(),
             1.0, i0data_sorted, x1.size()*x0.size(), i1data_sorted, x1.size()*x0.size(),
             1.0, odata_sorted, a2.size()*a4.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, a2.size(), a4.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task919::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1129
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x1, x3, x0, x2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x1, x3, x0, x2)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x1.size(), x3.size(), x0.size(), x2.size());
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x3, c3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x3, c3, x2)]);
      sort_indices<1,3,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), x3.size(), c3.size(), x2.size());
      zgemm3m_("T", "N", x1.size()*x0.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x1, x0);
}

void Task920::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  for (auto& c5 : *range_[0]) {
    for (auto& c6 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c5, a4, c6, a2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c5, a4, c6, a2)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, c5.size(), a4.size(), c6.size(), a2.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c6, c3, c5);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c6, c3, c5)]);
      sort_indices<3,1,0,2,0,1,2,1>(i1data, i1data_sorted, c1.size(), c6.size(), c3.size(), c5.size());
      zgemm3m_("T", "N", a4.size()*a2.size(), c1.size()*c3.size(), c6.size()*c5.size(),
             1.0, i0data_sorted, c6.size()*c5.size(), i1data_sorted, c6.size()*c5.size(),
             1.0, odata_sorted, a4.size()*a2.size());
    }
  }
  sort_indices<2,3,1,0,1,1,1,1>(odata_sorted, odata, a4.size(), a2.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task921::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  for (auto& c5 : *range_[0]) {
    for (auto& c6 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c5, a2, c6, a4);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c5, a2, c6, a4)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, c5.size(), a2.size(), c6.size(), a4.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c6, c3, c5);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c6, c3, c5)]);
      sort_indices<3,1,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), c6.size(), c3.size(), c5.size());
      zgemm3m_("T", "N", a2.size()*a4.size(), c1.size()*c3.size(), c6.size()*c5.size(),
             1.0, i0data_sorted, c6.size()*c5.size(), i1data_sorted, c6.size()*c5.size(),
             1.0, odata_sorted, a2.size()*a4.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, a2.size(), a4.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task922::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  for (auto& a6 : *range_[2]) {
    for (auto& a5 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a6, c3, a5);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a6, c3, a5)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a6.size(), c3.size(), a5.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a6, a2, a5, a4);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a6, a2, a5, a4)]);
      sort_indices<0,2,1,3,0,1,2,1>(i1data, i1data_sorted, a6.size(), a2.size(), a5.size(), a4.size());
      zgemm3m_("T", "N", c1.size()*c3.size(), a2.size()*a4.size(), a6.size()*a5.size(),
             1.0, i0data_sorted, a6.size()*a5.size(), i1data_sorted, a6.size()*a5.size(),
             1.0, odata_sorted, c1.size()*c3.size());
    }
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, c1.size(), c3.size(), a2.size(), a4.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task923::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  for (auto& a5 : *range_[2]) {
    for (auto& a6 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a5, c3, a6);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a5, c3, a6)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a5.size(), c3.size(), a6.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a6, a2, a5, a4);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a6, a2, a5, a4)]);
      sort_indices<2,0,1,3,0,1,-2,1>(i1data, i1data_sorted, a6.size(), a2.size(), a5.size(), a4.size());
      zgemm3m_("T", "N", c1.size()*c3.size(), a2.size()*a4.size(), a6.size()*a5.size(),
             1.0, i0data_sorted, a6.size()*a5.size(), i1data_sorted, a6.size()*a5.size(),
             1.0, odata_sorted, c1.size()*c3.size());
    }
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, c1.size(), c3.size(), a2.size(), a4.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task924::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, a2, x2, a4);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, a2, x2, a4)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a2.size(), x2.size(), a4.size());
      // tensor label: I1372
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x3, x2)]);
      sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x3.size(), x2.size());
      zgemm3m_("T", "N", a2.size()*a4.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, a2.size()*a4.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, a2.size(), a4.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task925::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I1372
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x3, x2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x3, x2), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x0 : *range_[1]) {
      // tensor label: Gamma511
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, x1, x2, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, x1, x2, x0)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x1.size(), x2.size(), x0.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x1, c3, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x1, c3, x0)]);
      sort_indices<1,3,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), x1.size(), c3.size(), x0.size());
      zgemm3m_("T", "N", x3.size()*x2.size(), c1.size()*c3.size(), x1.size()*x0.size(),
             1.0, i0data_sorted, x1.size()*x0.size(), i1data_sorted, x1.size()*x0.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x3, x2);
}

void Task926::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  // scalar
  // tensor label: Gamma566
  std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block();
  std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size()]);
  sort_indices<0,1,1,1>(i0data, i0data_sorted);
  // tensor label: I1713
  std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, a4, c3, a2);
  std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, a4, c3, a2)]);
  sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c1.size(), a4.size(), c3.size(), a2.size());
  zgemm3m_("T", "N", 1, c1.size()*a4.size()*c3.size()*a2.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, 1);
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a4.size(), c3.size(), a2.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task927::Task_local::compute() {
  const Index c1 = b(0);
  const Index a4 = b(1);
  const Index c3 = b(2);
  const Index a2 = b(3);
  // tensor label: I1713
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, a4, c3, a2);
  {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a4, c3, a2);
    sort_indices<0,1,2,3,1,1,2,1>(i0data, odata, c1.size(), a4.size(), c3.size(), a2.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(c1, a2, c3, a4);
    sort_indices<0,3,2,1,1,1,-2,1>(i1data, odata, c1.size(), a2.size(), c3.size(), a4.size());
  }
  out()->put_block(odata, c1, a4, c3, a2);
}

void Task928::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index a4 = b(3);
  // tensor label: I1128
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, a2, a4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, a2, a4), 0.0);
  // scalar
  // tensor label: Gamma568
  std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block();
  std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size()]);
  sort_indices<0,1,1,1>(i0data, i0data_sorted);
  // tensor label: I1717
  std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, a4, c3, a2);
  std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, a4, c3, a2)]);
  sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c1.size(), a4.size(), c3.size(), a2.size());
  zgemm3m_("T", "N", 1, c1.size()*a4.size()*c3.size()*a2.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, 1);
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a4.size(), c3.size(), a2.size());
  out()->put_block(odata, c1, c3, a2, a4);
}

void Task929::Task_local::compute() {
  const Index c1 = b(0);
  const Index a4 = b(1);
  const Index c3 = b(2);
  const Index a2 = b(3);
  // tensor label: I1717
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, a4, c3, a2);
  {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a4, c3, a2);
    sort_indices<0,1,2,3,1,1,1,1>(i0data, odata, c1.size(), a4.size(), c3.size(), a2.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(c1, a2, c3, a4);
    sort_indices<0,3,2,1,1,1,-1,1>(i1data, odata, c1.size(), a2.size(), c3.size(), a4.size());
  }
  out()->put_block(odata, c1, a4, c3, a2);
}

void Task930::Task_local::compute() {
  const Index x1 = b(0);
  const Index a2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: r
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, a2, x0, a1);
  {
    // tensor label: I1656
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x1, x0, a1, a2);
    sort_indices<0,3,1,2,1,1,1,1>(i0data, odata, x1.size(), x0.size(), a1.size(), a2.size());
  }
  out()->put_block(odata, x1, a2, x0, a1);
}

void Task931::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index a1 = b(2);
  const Index a2 = b(3);
  // tensor label: I1656
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, a1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, a1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, a1, a2), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& c4 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c3, a1, c4, a2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c3, a1, c4, a2)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, c3.size(), a1.size(), c4.size(), a2.size());
      // tensor label: I1657
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c4, c3, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c4, c3, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, c4.size(), c3.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", a1.size()*a2.size(), x1.size()*x0.size(), c4.size()*c3.size(),
             1.0, i0data_sorted, c4.size()*c3.size(), i1data_sorted, c4.size()*c3.size(),
             1.0, odata_sorted, a1.size()*a2.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, a1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, x1, x0, a1, a2);
}

void Task932::Task_local::compute() {
  const Index c4 = b(0);
  const Index c3 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1657
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c4, c3, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c4, c3, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c4, c3, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma511
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, x1, x2, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, x1, x2, x0)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x1.size(), x2.size(), x0.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, c4, x2, c3);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, c4, x2, c3)]);
      sort_indices<0,2,1,3,0,1,-2,1>(i1data, i1data_sorted, x3.size(), c4.size(), x2.size(), c3.size());
      zgemm3m_("T", "N", x1.size()*x0.size(), c4.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), c4.size(), c3.size());
  out()->put_block(odata, c4, c3, x1, x0);
}

void Task933::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index a1 = b(2);
  const Index a2 = b(3);
  // tensor label: I1656
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, a1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, a1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, a1, a2), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma511
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, x1, x2, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, x1, x2, x0)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x1.size(), x2.size(), x0.size());
      // tensor label: I1690
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a1, a2, x3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a1, a2, x3, x2)]);
      sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, a1.size(), a2.size(), x3.size(), x2.size());
      zgemm3m_("T", "N", x1.size()*x0.size(), a1.size()*a2.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a1.size(), a2.size());
  out()->put_block(odata, x1, x0, a1, a2);
}

void Task934::Task_local::compute() {
  const Index a1 = b(0);
  const Index a2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I1690
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a1, a2, x3, x2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a1, a2, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, a2, x3, x2), 0.0);
  for (auto& a3 : *range_[2]) {
    for (auto& a4 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, a3, x2, a4);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, a3, x2, a4)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), a3.size(), x2.size(), a4.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a4, a1, a3, a2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a4, a1, a3, a2)]);
      sort_indices<2,0,1,3,0,1,-2,1>(i1data, i1data_sorted, a4.size(), a1.size(), a3.size(), a2.size());
      zgemm3m_("T", "N", x3.size()*x2.size(), a1.size()*a2.size(), a4.size()*a3.size(),
             1.0, i0data_sorted, a4.size()*a3.size(), i1data_sorted, a4.size()*a3.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), a1.size(), a2.size());
  out()->put_block(odata, a1, a2, x3, x2);
}

void Task935::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index a1 = b(2);
  const Index a2 = b(3);
  // tensor label: I1656
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, a1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, a1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, a1, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      // tensor label: Gamma574
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x0, x4, x1);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x0, x4, x1)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x1.size());
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x5, a1, x4, a2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x5, a1, x4, a2)]);
      sort_indices<0,2,1,3,0,1,-2,1>(i1data, i1data_sorted, x5.size(), a1.size(), x4.size(), a2.size());
      zgemm3m_("T", "N", x0.size()*x1.size(), a1.size()*a2.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<1,0,2,3,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a1.size(), a2.size());
  out()->put_block(odata, x1, x0, a1, a2);
}

void Task936::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index a1 = b(2);
  const Index a2 = b(3);
  // tensor label: I1656
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, a1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, a1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, a1, a2), 0.0);
  for (auto& x7 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      // tensor label: Gamma575
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, x0, x6, x1);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, x0, x6, x1)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x7.size(), x0.size(), x6.size(), x1.size());
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x7, a1, x6, a2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x7, a1, x6, a2)]);
      sort_indices<0,2,1,3,0,1,-1,1>(i1data, i1data_sorted, x7.size(), a1.size(), x6.size(), a2.size());
      zgemm3m_("T", "N", x0.size()*x1.size(), a1.size()*a2.size(), x7.size()*x6.size(),
             1.0, i0data_sorted, x7.size()*x6.size(), i1data_sorted, x7.size()*x6.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<1,0,2,3,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a1.size(), a2.size());
  out()->put_block(odata, x1, x0, a1, a2);
}

void Task938::Task_local::compute() {
  const Index c1 = b(0);
  const Index x2 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: r
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x2, x0, x1);
  {
    // tensor label: I1732
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x2, x1, x0, c1);
    sort_indices<3,0,2,1,1,1,1,1>(i0data, odata, x2.size(), x1.size(), x0.size(), c1.size());
  }
  out()->put_block(odata, c1, x2, x0, x1);
}

void Task939::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index c1 = b(3);
  // tensor label: I1732
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x2, x1, x0, c1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: h1
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, x3);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, x3)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size());
    // tensor label: Gamma5
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x2, x3, x1, x0);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x2, x3, x1, x0)]);
    sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, x2.size(), x3.size(), x1.size(), x0.size());
    zgemm3m_("T", "N", c1.size(), x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c1.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, c1.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x2, x1, x0, c1);
}

void Task940::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index c1 = b(3);
  // tensor label: I1732
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x2, x1, x0, c1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, c1), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, x5, x4, x3);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, x5, x4, x3)]);
        sort_indices<1,2,3,0,0,1,1,1>(i0data, i0data_sorted, c1.size(), x5.size(), x4.size(), x3.size());
        // tensor label: Gamma108
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x2, x5, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x2, x5, x4, x3, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,2>(i1data, i1data_sorted, x2.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", c1.size(), x2.size()*x1.size()*x0.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, c1.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x2, x1, x0, c1);
}

void Task941::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index c1 = b(3);
  // tensor label: I1732
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x2, x1, x0, c1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, c1), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, c1, x3);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, c1, x3)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c1.size(), x3.size());
        // tensor label: Gamma4
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x5, x4, x2, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x5, x4, x2, x3, x1, x0)]);
        sort_indices<0,1,3,2,4,5,0,1,1,2>(i1data, i1data_sorted, x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", c1.size(), x2.size()*x1.size()*x0.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, c1.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x2, x1, x0, c1);
}

void Task942::Task_local::compute() {
  const Index c2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: r
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c2, x1, x0, a1);
  {
    // tensor label: I1734
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x1, x0, c2, a1);
    sort_indices<2,0,1,3,1,1,1,1>(i0data, odata, x1.size(), x0.size(), c2.size(), a1.size());
  }
  out()->put_block(odata, c2, x1, x0, a1);
}

void Task943::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I1734
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, c2, a1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, c2, a1), 0.0);
  // tensor label: h1
  std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c2, a1);
  std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c2, a1)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c2.size(), a1.size());
  // tensor label: Gamma34
  std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x1, x0);
  std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x1, x0)]);
  sort_indices<0,1,0,1,-1,1>(i1data, i1data_sorted, x1.size(), x0.size());
  zgemm3m_("T", "N", c2.size()*a1.size(), x1.size()*x0.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c2.size()*a1.size());
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), x1.size(), x0.size());
  out()->put_block(odata, x1, x0, c2, a1);
}

void Task944::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I1734
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, c2, a1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, c2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c2, a1, x3, x2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c2, a1, x3, x2)]);
      sort_indices<2,3,0,1,0,1,1,1>(i0data, i0data_sorted, c2.size(), a1.size(), x3.size(), x2.size());
      // tensor label: Gamma31
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, x2, x1, x0)]);
      sort_indices<0,1,2,3,0,1,-1,2>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c2.size()*a1.size(), x1.size()*x0.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c2.size()*a1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), x1.size(), x0.size());
  out()->put_block(odata, x1, x0, c2, a1);
}

void Task945::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I1734
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, c2, a1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, c2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c2, x3, x2, a1);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c2, x3, x2, a1)]);
      sort_indices<1,2,0,3,0,1,1,1>(i0data, i0data_sorted, c2.size(), x3.size(), x2.size(), a1.size());
      // tensor label: Gamma25
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x1, x3, x2, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x1, x3, x2, x0)]);
      sort_indices<1,2,0,3,0,1,-1,2>(i1data, i1data_sorted, x1.size(), x3.size(), x2.size(), x0.size());
      zgemm3m_("T", "N", c2.size()*a1.size(), x1.size()*x0.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c2.size()*a1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), x1.size(), x0.size());
  out()->put_block(odata, x1, x0, c2, a1);
}

void Task946::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I1734
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, c2, a1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, c2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, a1, c2, x2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, a1, c2, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), a1.size(), c2.size(), x2.size());
      // tensor label: Gamma28
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, x0, x1, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, x0, x1, x2)]);
      sort_indices<0,3,1,2,0,1,1,2>(i1data, i1data_sorted, x3.size(), x0.size(), x1.size(), x2.size());
      zgemm3m_("T", "N", a1.size()*c2.size(), x0.size()*x1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, a1.size()*c2.size());
    }
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, a1.size(), c2.size(), x0.size(), x1.size());
  out()->put_block(odata, x1, x0, c2, a1);
}

void Task947::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I1734
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, c2, a1);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, c2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, x2, c2, a1);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, x2, c2, a1)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), c2.size(), a1.size());
      // tensor label: Gamma31
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, x2, x1, x0)]);
      sort_indices<0,1,2,3,0,1,-1,2>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c2.size()*a1.size(), x1.size()*x0.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c2.size()*a1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), x1.size(), x0.size());
  out()->put_block(odata, x1, x0, c2, a1);
}

void Task948::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index c1 = b(2);
  const Index a2 = b(3);
  // tensor label: r
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x0, x1, c1, a2);
  {
    // tensor label: I1736
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x1, x0, c1, a2);
    sort_indices<1,0,2,3,1,1,1,1>(i0data, odata, x1.size(), x0.size(), c1.size(), a2.size());
  }
  out()->put_block(odata, x0, x1, c1, a2);
}

void Task949::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index c1 = b(2);
  const Index a2 = b(3);
  // tensor label: I1736
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x1, x0, c1, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x1, x0, c1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, c1, a2), 0.0);
  // tensor label: h1
  std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a2);
  std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a2)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size());
  // tensor label: Gamma34
  std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x1, x0);
  std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x1, x0)]);
  sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, x1.size(), x0.size());
  zgemm3m_("T", "N", c1.size()*a2.size(), x1.size()*x0.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c1.size()*a2.size());
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, x1, x0, c1, a2);
}

#endif

//
// BAGEL - Parallel electron correlation program.
// Filename: RelMRCI_tasks11.cc
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

#include <src/smith/RelMRCI_tasks11.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::RelMRCI;

void Task500::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& c3 : *range_[0]) {
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, a2, x2, c3);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, a2, x2, c3)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, x3.size(), a2.size(), x2.size(), c3.size());
        // tensor label: I852
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x3, x2, x1, x0)]);
        sort_indices<2,3,1,0,4,5,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x3.size(), x2.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", a2.size(), c1.size()*x1.size()*x0.size(), c3.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, c3.size()*x3.size()*x2.size(), i1data_sorted, c3.size()*x3.size()*x2.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task501::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I852
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x3, x2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x3, x2, x1, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      // tensor label: Gamma111
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x3, x5, x2, x4, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x3, x5, x2, x4, x1, x0)]);
      sort_indices<1,3,0,2,4,5,0,1,1,1>(i0data, i0data_sorted, x3.size(), x5.size(), x2.size(), x4.size(), x1.size(), x0.size());
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x5, c3, x4);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x5, c3, x4)]);
      sort_indices<1,3,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), x5.size(), c3.size(), x4.size());
      zgemm3m_("T", "N", x3.size()*x2.size()*x1.size()*x0.size(), c1.size()*c3.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, x3.size()*x2.size()*x1.size()*x0.size());
    }
  }
  sort_indices<4,5,0,1,2,3,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), x1.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x3, x2, x1, x0);
}

void Task502::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x4, a2, x3, x2);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x4, a2, x3, x2)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, x4.size(), a2.size(), x3.size(), x2.size());
        // tensor label: I855
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x4, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x4, x3, x2, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,1>(i1data, i1data_sorted, c1.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", a2.size(), c1.size()*x1.size()*x0.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task503::Task_local::compute() {
  const Index c1 = b(0);
  const Index x4 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I855
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x4, x3, x2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x4, x3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x4, x3, x2, x1, x0), 0.0);
  for (auto& x7 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: Gamma284
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, x6, x4, x5, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, x6, x4, x5, x3, x2, x1, x0)]);
        sort_indices<0,1,3,2,4,5,6,7,0,1,1,1>(i0data, i0data_sorted, x7.size(), x6.size(), x4.size(), x5.size(), x3.size(), x2.size(), x1.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x7, x6, c1, x5);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x7, x6, c1, x5)]);
        sort_indices<0,1,3,2,0,1,1,2>(i1data, i1data_sorted, x7.size(), x6.size(), c1.size(), x5.size());
        zgemm3m_("T", "N", x4.size()*x3.size()*x2.size()*x1.size()*x0.size(), c1.size(), x7.size()*x6.size()*x5.size(),
               1.0, i0data_sorted, x7.size()*x6.size()*x5.size(), i1data_sorted, x7.size()*x6.size()*x5.size(),
               1.0, odata_sorted, x4.size()*x3.size()*x2.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<5,0,1,2,3,4,1,1,1,1>(odata_sorted, odata, x4.size(), x3.size(), x2.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, c1, x4, x3, x2, x1, x0);
}

void Task504::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x4, x3, x2, a2);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x4, x3, x2, a2)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x4.size(), x3.size(), x2.size(), a2.size());
        // tensor label: I858
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x2, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x2, x4, x3, x1, x0)]);
        sort_indices<2,3,1,0,4,5,0,1,1,1>(i1data, i1data_sorted, c1.size(), x2.size(), x4.size(), x3.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", a2.size(), c1.size()*x1.size()*x0.size(), x2.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x2.size()*x4.size()*x3.size(), i1data_sorted, x2.size()*x4.size()*x3.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task505::Task_local::compute() {
  const Index c1 = b(0);
  const Index x2 = b(1);
  const Index x4 = b(2);
  const Index x3 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I858
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x2, x4, x3, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x2, x4, x3, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x2, x4, x3, x1, x0), 0.0);
  for (auto& x7 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: Gamma104
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, x6, x2, x5, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, x6, x2, x5, x4, x3, x1, x0)]);
        sort_indices<0,1,3,2,4,5,6,7,0,1,1,1>(i0data, i0data_sorted, x7.size(), x6.size(), x2.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x7, x6, c1, x5);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x7, x6, c1, x5)]);
        sort_indices<0,1,3,2,0,1,1,2>(i1data, i1data_sorted, x7.size(), x6.size(), c1.size(), x5.size());
        zgemm3m_("T", "N", x2.size()*x4.size()*x3.size()*x1.size()*x0.size(), c1.size(), x7.size()*x6.size()*x5.size(),
               1.0, i0data_sorted, x7.size()*x6.size()*x5.size(), i1data_sorted, x7.size()*x6.size()*x5.size(),
               1.0, odata_sorted, x2.size()*x4.size()*x3.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<5,0,1,2,3,4,1,1,1,1>(odata_sorted, odata, x2.size(), x4.size(), x3.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, c1, x2, x4, x3, x1, x0);
}

void Task506::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& c3 : *range_[0]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x2, c3, c1, a2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x2, c3, c1, a2)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x2.size(), c3.size(), c1.size(), a2.size());
      // tensor label: I861
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c3, x2, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, c3.size(), x2.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c1.size()*a2.size(), x1.size()*x0.size(), c3.size()*x2.size(),
             1.0, i0data_sorted, c3.size()*x2.size(), i1data_sorted, c3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task507::Task_local::compute() {
  const Index c3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I861
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x2, x1, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma4
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x2, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x2, x3, x1, x0)]);
        sort_indices<0,1,3,2,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x5, x4, c3, x3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x5, x4, c3, x3)]);
        sort_indices<0,1,3,2,0,1,1,1>(i1data, i1data_sorted, x5.size(), x4.size(), c3.size(), x3.size());
        zgemm3m_("T", "N", x2.size()*x1.size()*x0.size(), c3.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, x2.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x2.size(), x1.size(), x0.size(), c3.size());
  out()->put_block(odata, c3, x2, x1, x0);
}

void Task508::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& c3 : *range_[0]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x2, a2, c1, c3);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x2, a2, c1, c3)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, x2.size(), a2.size(), c1.size(), c3.size());
      // tensor label: I864
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c3, x2, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, c3.size(), x2.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", a2.size()*c1.size(), x1.size()*x0.size(), c3.size()*x2.size(),
             1.0, i0data_sorted, c3.size()*x2.size(), i1data_sorted, c3.size()*x2.size(),
             1.0, odata_sorted, a2.size()*c1.size());
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task509::Task_local::compute() {
  const Index c3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I864
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x2, x1, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma4
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x2, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x2, x3, x1, x0)]);
        sort_indices<0,1,3,2,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x5, x4, c3, x3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x5, x4, c3, x3)]);
        sort_indices<0,1,3,2,0,1,-1,1>(i1data, i1data_sorted, x5.size(), x4.size(), c3.size(), x3.size());
        zgemm3m_("T", "N", x2.size()*x1.size()*x0.size(), c3.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, x2.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x2.size(), x1.size(), x0.size(), c3.size());
  out()->put_block(odata, c3, x2, x1, x0);
}

void Task510::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c3, a2, c1, x5);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c3, a2, c1, x5)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), c1.size(), x5.size());
      // tensor label: I867
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c3, x5, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c3, x5, x1, x0)]);
      sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c3.size(), x5.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", a2.size()*c1.size(), x1.size()*x0.size(), c3.size()*x5.size(),
             1.0, i0data_sorted, c3.size()*x5.size(), i1data_sorted, c3.size()*x5.size(),
             1.0, odata_sorted, a2.size()*c1.size());
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task511::Task_local::compute() {
  const Index c3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I867
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x5, x1, x0), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma225
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x4, x5, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x4, x5, x3, x2, x1, x0)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x4.size(), x5.size(), x3.size(), x2.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, c3, x3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, c3, x3, x2)]);
        sort_indices<0,2,3,1,0,1,-1,2>(i1data, i1data_sorted, x4.size(), c3.size(), x3.size(), x2.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), c3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), c3.size());
  out()->put_block(odata, c3, x5, x1, x0);
}

void Task512::Task_local::compute() {
  const Index c3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I867
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x5, x1, x0), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma108
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x2, x5, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x2, x5, x4, x3, x1, x0)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x2.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, x3, x2, c3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, x3, x2, c3)]);
        sort_indices<2,0,1,3,0,1,-1,2>(i1data, i1data_sorted, x4.size(), x3.size(), x2.size(), c3.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), c3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), c3.size());
  out()->put_block(odata, c3, x5, x1, x0);
}

void Task513::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a2, c3, x5);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a2, c3, x5)]);
      sort_indices<2,3,0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x5.size());
      // tensor label: I870
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c3, x5, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c3, x5, x1, x0)]);
      sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c3.size(), x5.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c1.size()*a2.size(), x1.size()*x0.size(), c3.size()*x5.size(),
             1.0, i0data_sorted, c3.size()*x5.size(), i1data_sorted, c3.size()*x5.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task514::Task_local::compute() {
  const Index c3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I870
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x5, x1, x0), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma225
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x4, x5, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x4, x5, x3, x2, x1, x0)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x4.size(), x5.size(), x3.size(), x2.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, c3, x3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, c3, x3, x2)]);
        sort_indices<0,2,3,1,0,1,1,2>(i1data, i1data_sorted, x4.size(), c3.size(), x3.size(), x2.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), c3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), c3.size());
  out()->put_block(odata, c3, x5, x1, x0);
}

void Task515::Task_local::compute() {
  const Index c3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I870
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x5, x1, x0), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma108
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x2, x5, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x2, x5, x4, x3, x1, x0)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x2.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, x3, x2, c3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, x3, x2, c3)]);
        sort_indices<2,0,1,3,0,1,1,2>(i1data, i1data_sorted, x4.size(), x3.size(), x2.size(), c3.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), c3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), c3.size());
  out()->put_block(odata, c3, x5, x1, x0);
}

void Task516::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x7 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      // tensor label: Gamma245
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, x6, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, x6, x1, x0)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x7.size(), x6.size(), x1.size(), x0.size());
      // tensor label: I897
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x7, a2, c1, x6);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x7, a2, c1, x6)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x7.size(), a2.size(), c1.size(), x6.size());
      zgemm3m_("T", "N", x1.size()*x0.size(), a2.size()*c1.size(), x7.size()*x6.size(),
             1.0, i0data_sorted, x7.size()*x6.size(), i1data_sorted, x7.size()*x6.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), c1.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task517::Task_local::compute() {
  const Index x7 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x6 = b(3);
  // tensor label: I897
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x7, a2, c1, x6);
  {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, a2, c1, x6);
    sort_indices<0,1,2,3,1,1,-1,2>(i0data, odata, x7.size(), a2.size(), c1.size(), x6.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(c1, a2, x7, x6);
    sort_indices<2,1,0,3,1,1,1,2>(i1data, odata, c1.size(), a2.size(), x7.size(), x6.size());
  }
  out()->put_block(odata, x7, a2, c1, x6);
}

void Task518::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& c3 : *range_[0]) {
      for (auto& x4 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a2, c3, x4);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a2, c3, x4)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, x5.size(), a2.size(), c3.size(), x4.size());
        // tensor label: I899
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x5, x4, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x5, x4, x1, x0)]);
        sort_indices<2,1,3,0,4,5,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x5.size(), x4.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", a2.size(), c1.size()*x1.size()*x0.size(), c3.size()*x5.size()*x4.size(),
               1.0, i0data_sorted, c3.size()*x5.size()*x4.size(), i1data_sorted, c3.size()*x5.size()*x4.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task519::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x5 = b(2);
  const Index x4 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I899
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x5, x4, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x5, x4, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x5, x4, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma246
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x3, x2, x1, x0)]);
      sort_indices<2,3,0,1,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
      // tensor label: I900
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x3, x2)]);
      sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x3.size(), x2.size());
      zgemm3m_("T", "N", x5.size()*x4.size()*x1.size()*x0.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x5.size()*x4.size()*x1.size()*x0.size());
    }
  }
  sort_indices<4,5,0,1,2,3,1,1,1,1>(odata_sorted, odata, x5.size(), x4.size(), x1.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x5, x4, x1, x0);
}

void Task520::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I900
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x3, x2);
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, c3, x3, x2);
    sort_indices<0,1,2,3,1,1,1,2>(i0data, odata, c1.size(), c3.size(), x3.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(x3, x2, c1, c3);
    sort_indices<2,3,0,1,1,1,1,2>(i1data, odata, x3.size(), x2.size(), c1.size(), c3.size());
  }
  out()->put_block(odata, c1, c3, x3, x2);
}

void Task521::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x5 = b(2);
  const Index x4 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I899
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x5, x4, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x5, x4, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x5, x4, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma7
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x3, x2, x4, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x3, x2, x4, x1, x0)]);
      sort_indices<1,2,0,3,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x3.size(), x2.size(), x4.size(), x1.size(), x0.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x3, x2, c3);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x3, x2, c3)]);
      sort_indices<1,2,0,3,0,1,1,2>(i1data, i1data_sorted, c1.size(), x3.size(), x2.size(), c3.size());
      zgemm3m_("T", "N", x5.size()*x4.size()*x1.size()*x0.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x5.size()*x4.size()*x1.size()*x0.size());
    }
  }
  sort_indices<4,5,0,1,2,3,1,1,1,1>(odata_sorted, odata, x5.size(), x4.size(), x1.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x5, x4, x1, x0);
}

void Task522::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x5 = b(2);
  const Index x4 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I899
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x5, x4, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x5, x4, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x5, x4, x1, x0), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: Gamma303
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x2, x3, x4, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x2, x3, x4, x1, x0)]);
      sort_indices<1,2,0,3,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x2.size(), x3.size(), x4.size(), x1.size(), x0.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, c3, c1, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, c3, c1, x2)]);
      sort_indices<3,0,1,2,0,1,-1,2>(i1data, i1data_sorted, x3.size(), c3.size(), c1.size(), x2.size());
      zgemm3m_("T", "N", x5.size()*x4.size()*x1.size()*x0.size(), c3.size()*c1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x5.size()*x4.size()*x1.size()*x0.size());
    }
  }
  sort_indices<5,4,0,1,2,3,1,1,1,1>(odata_sorted, odata, x5.size(), x4.size(), x1.size(), x0.size(), c3.size(), c1.size());
  out()->put_block(odata, c1, c3, x5, x4, x1, x0);
}

void Task523::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        for (auto& x2 : *range_[1]) {
          // tensor label: Gamma246
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x3, x2, x1, x0)]);
          sort_indices<0,1,2,3,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
          // tensor label: I902
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a2, x3, x2, x5, c1, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a2, x3, x2, x5, c1, x4)]);
          sort_indices<3,5,1,2,0,4,0,1,1,1>(i1data, i1data_sorted, a2.size(), x3.size(), x2.size(), x5.size(), c1.size(), x4.size());
          zgemm3m_("T", "N", x1.size()*x0.size(), a2.size()*c1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x1.size()*x0.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), c1.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task524::Task_local::compute() {
  const Index a2 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x5 = b(3);
  const Index c1 = b(4);
  const Index x4 = b(5);
  // tensor label: I902
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a2, x3, x2, x5, c1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a2, x3, x2, x5, c1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, x3, x2, x5, c1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a3, c1, x4);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a3, c1, x4)]);
    sort_indices<1,0,2,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), a3.size(), c1.size(), x4.size());
    // tensor label: I903
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, a2, x3, x2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, a2, x3, x2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), a2.size(), x3.size(), x2.size());
    zgemm3m_("T", "N", x5.size()*c1.size()*x4.size(), a2.size()*x3.size()*x2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, x5.size()*c1.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), c1.size(), x4.size(), a2.size(), x3.size(), x2.size());
  out()->put_block(odata, a2, x3, x2, x5, c1, x4);
}

void Task525::Task_local::compute() {
  const Index a3 = b(0);
  const Index a2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I903
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, a2, x3, x2);
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(a3, a2, x3, x2);
    sort_indices<0,1,2,3,1,1,-1,2>(i0data, odata, a3.size(), a2.size(), x3.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(x3, x2, a3, a2);
    sort_indices<2,3,0,1,1,1,-1,2>(i1data, odata, x3.size(), x2.size(), a3.size(), a2.size());
  }
  out()->put_block(odata, a3, a2, x3, x2);
}

void Task526::Task_local::compute() {
  const Index a2 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x5 = b(3);
  const Index c1 = b(4);
  const Index x4 = b(5);
  // tensor label: I902
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a2, x3, x2, x5, c1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a2, x3, x2, x5, c1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, x3, x2, x5, c1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a3, x5, x4);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a3, x5, x4)]);
    sort_indices<1,0,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a3.size(), x5.size(), x4.size());
    // tensor label: I935
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, a2, x3, x2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, a2, x3, x2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), a2.size(), x3.size(), x2.size());
    zgemm3m_("T", "N", c1.size()*x5.size()*x4.size(), a2.size()*x3.size()*x2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, c1.size()*x5.size()*x4.size());
  }
  sort_indices<3,4,5,1,0,2,1,1,1,1>(odata_sorted, odata, c1.size(), x5.size(), x4.size(), a2.size(), x3.size(), x2.size());
  out()->put_block(odata, a2, x3, x2, x5, c1, x4);
}

void Task527::Task_local::compute() {
  const Index a3 = b(0);
  const Index a2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I935
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, a2, x3, x2);
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(a3, a2, x3, x2);
    sort_indices<0,1,2,3,1,1,1,2>(i0data, odata, a3.size(), a2.size(), x3.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(x3, a2, a3, x2);
    sort_indices<2,1,0,3,1,1,-1,2>(i1data, odata, x3.size(), a2.size(), a3.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i2data = in(0)->get_block(x3, x2, a3, a2);
    sort_indices<2,3,0,1,1,1,1,2>(i2data, odata, x3.size(), x2.size(), a3.size(), a2.size());
  }
  out()->put_block(odata, a3, a2, x3, x2);
}

void Task528::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        for (auto& x4 : *range_[1]) {
          // tensor label: Gamma7
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x3, x2, x4, x1, x0);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x3, x2, x4, x1, x0)]);
          sort_indices<0,1,2,3,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x3.size(), x2.size(), x4.size(), x1.size(), x0.size());
          // tensor label: I908
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, x2, a2, x5, c1, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, x2, a2, x5, c1, x4)]);
          sort_indices<3,0,1,5,2,4,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), a2.size(), x5.size(), c1.size(), x4.size());
          zgemm3m_("T", "N", x1.size()*x0.size(), a2.size()*c1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x1.size()*x0.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), c1.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task529::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index a2 = b(2);
  const Index x5 = b(3);
  const Index c1 = b(4);
  const Index x4 = b(5);
  // tensor label: I908
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x3, x2, a2, x5, c1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x3, x2, a2, x5, c1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2, a2, x5, c1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a3, c1, x4);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a3, c1, x4)]);
    sort_indices<1,0,2,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), a3.size(), c1.size(), x4.size());
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x3, x2, a2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x3, x2, a2)]);
    sort_indices<0,1,2,3,0,1,-1,2>(i1data, i1data_sorted, a3.size(), x3.size(), x2.size(), a2.size());
    zgemm3m_("T", "N", x5.size()*c1.size()*x4.size(), x3.size()*x2.size()*a2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, x5.size()*c1.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), c1.size(), x4.size(), x3.size(), x2.size(), a2.size());
  out()->put_block(odata, x3, x2, a2, x5, c1, x4);
}

void Task530::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        for (auto& x4 : *range_[1]) {
          // tensor label: Gamma303
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x2, x3, x4, x1, x0);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x2, x3, x4, x1, x0)]);
          sort_indices<0,1,2,3,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x2.size(), x3.size(), x4.size(), x1.size(), x0.size());
          // tensor label: I914
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, a2, x2, x5, c1, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, a2, x2, x5, c1, x4)]);
          sort_indices<3,2,0,5,1,4,0,1,1,1>(i1data, i1data_sorted, x3.size(), a2.size(), x2.size(), x5.size(), c1.size(), x4.size());
          zgemm3m_("T", "N", x1.size()*x0.size(), a2.size()*c1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x1.size()*x0.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), c1.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task531::Task_local::compute() {
  const Index x3 = b(0);
  const Index a2 = b(1);
  const Index x2 = b(2);
  const Index x5 = b(3);
  const Index c1 = b(4);
  const Index x4 = b(5);
  // tensor label: I914
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x3, a2, x2, x5, c1, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x3, a2, x2, x5, c1, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, a2, x2, x5, c1, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a3, c1, x4);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a3, c1, x4)]);
    sort_indices<1,0,2,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), a3.size(), c1.size(), x4.size());
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, a2, a3, x2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, a2, a3, x2)]);
    sort_indices<2,0,1,3,0,1,1,2>(i1data, i1data_sorted, x3.size(), a2.size(), a3.size(), x2.size());
    zgemm3m_("T", "N", x5.size()*c1.size()*x4.size(), x3.size()*a2.size()*x2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, x5.size()*c1.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), c1.size(), x4.size(), x3.size(), a2.size(), x2.size());
  out()->put_block(odata, x3, a2, x2, x5, c1, x4);
}

void Task532::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& x5 : *range_[1]) {
      for (auto& x4 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c3, a2, x5, x4);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c3, a2, x5, x4)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), x5.size(), x4.size());
        // tensor label: I931
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x5, x4, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x5, x4, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x5.size(), x4.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", a2.size(), c1.size()*x1.size()*x0.size(), c3.size()*x5.size()*x4.size(),
               1.0, i0data_sorted, c3.size()*x5.size()*x4.size(), i1data_sorted, c3.size()*x5.size()*x4.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task533::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x5 = b(2);
  const Index x4 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I931
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x5, x4, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x5, x4, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x5, x4, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma246
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x3, x2, x1, x0)]);
      sort_indices<2,3,0,1,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
      // tensor label: I932
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, c3, x3, x2);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, c3, x3, x2)]);
      sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x3.size(), x2.size());
      zgemm3m_("T", "N", x5.size()*x4.size()*x1.size()*x0.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x5.size()*x4.size()*x1.size()*x0.size());
    }
  }
  sort_indices<4,5,0,1,2,3,1,1,1,1>(odata_sorted, odata, x5.size(), x4.size(), x1.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x5, x4, x1, x0);
}

void Task534::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I932
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x3, x2);
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, c3, x3, x2);
    sort_indices<0,1,2,3,1,1,-1,2>(i0data, odata, c1.size(), c3.size(), x3.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(0)->get_block(x3, c3, c1, x2);
    sort_indices<2,1,0,3,1,1,1,2>(i1data, odata, x3.size(), c3.size(), c1.size(), x2.size());
  }
  {
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i2data = in(0)->get_block(x3, x2, c1, c3);
    sort_indices<2,3,0,1,1,1,-1,2>(i2data, odata, x3.size(), x2.size(), c1.size(), c3.size());
  }
  out()->put_block(odata, c1, c3, x3, x2);
}

void Task535::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x5 = b(2);
  const Index x4 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I931
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, c3, x5, x4, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, c3, x5, x4, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x5, x4, x1, x0), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: Gamma4
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x2, x3, x1, x0);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x2, x3, x1, x0)]);
      sort_indices<2,3,0,1,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x3, x2, c3);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x3, x2, c3)]);
      sort_indices<2,1,0,3,0,1,-1,2>(i1data, i1data_sorted, c1.size(), x3.size(), x2.size(), c3.size());
      zgemm3m_("T", "N", x5.size()*x4.size()*x1.size()*x0.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x5.size()*x4.size()*x1.size()*x0.size());
    }
  }
  sort_indices<4,5,0,1,2,3,1,1,1,1>(odata_sorted, odata, x5.size(), x4.size(), x1.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, c1, c3, x5, x4, x1, x0);
}

void Task536::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        for (auto& x3 : *range_[1]) {
          // tensor label: Gamma4
          std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x2, x3, x1, x0);
          std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x2, x3, x1, x0)]);
          sort_indices<0,1,2,3,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
          // tensor label: I940
          std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x3, x2, a2, c1, x5, x4);
          std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x3, x2, a2, c1, x5, x4)]);
          sort_indices<4,5,1,0,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), a2.size(), c1.size(), x5.size(), x4.size());
          zgemm3m_("T", "N", x1.size()*x0.size(), a2.size()*c1.size(), x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, i0data_sorted, x3.size()*x2.size()*x5.size()*x4.size(), i1data_sorted, x3.size()*x2.size()*x5.size()*x4.size(),
                 1.0, odata_sorted, x1.size()*x0.size());
        }
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), c1.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task537::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index a2 = b(2);
  const Index c1 = b(3);
  const Index x5 = b(4);
  const Index x4 = b(5);
  // tensor label: I940
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(x3, x2, a2, c1, x5, x4);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(x3, x2, a2, c1, x5, x4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2, a2, c1, x5, x4), 0.0);
  for (auto& a3 : *range_[2]) {
    // tensor label: t2
    std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, a3, x5, x4);
    std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, a3, x5, x4)]);
    sort_indices<1,0,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a3.size(), x5.size(), x4.size());
    // tensor label: v2
    std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x3, x2, a2);
    std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x3, x2, a2)]);
    sort_indices<0,1,2,3,0,1,1,2>(i1data, i1data_sorted, a3.size(), x3.size(), x2.size(), a2.size());
    zgemm3m_("T", "N", c1.size()*x5.size()*x4.size(), x3.size()*x2.size()*a2.size(), a3.size(),
           1.0, i0data_sorted, a3.size(), i1data_sorted, a3.size(),
           1.0, odata_sorted, c1.size()*x5.size()*x4.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, c1.size(), x5.size(), x4.size(), x3.size(), x2.size(), a2.size());
  out()->put_block(odata, x3, x2, a2, c1, x5, x4);
}

void Task538::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x7 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, a2, x6, x5);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, a2, x6, x5)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, x7.size(), a2.size(), x6.size(), x5.size());
        // tensor label: I961
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x7, x6, x5, x1, x0);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x7, x6, x5, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,1>(i1data, i1data_sorted, c1.size(), x7.size(), x6.size(), x5.size(), x1.size(), x0.size());
        zgemm3m_("T", "N", a2.size(), c1.size()*x1.size()*x0.size(), x7.size()*x6.size()*x5.size(),
               1.0, i0data_sorted, x7.size()*x6.size()*x5.size(), i1data_sorted, x7.size()*x6.size()*x5.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task539::Task_local::compute() {
  const Index c1 = b(0);
  const Index x7 = b(1);
  const Index x6 = b(2);
  const Index x5 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I961
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x7, x6, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x7, x6, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x7, x6, x5, x1, x0), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma320
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, x4, x6, x5, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, x4, x6, x5, x3, x2, x1, x0)]);
        sort_indices<1,4,5,0,2,3,6,7,0,1,1,1>(i0data, i0data_sorted, x7.size(), x4.size(), x6.size(), x5.size(), x3.size(), x2.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(c1, x4, x3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(c1, x4, x3, x2)]);
        sort_indices<1,2,3,0,0,1,-1,2>(i1data, i1data_sorted, c1.size(), x4.size(), x3.size(), x2.size());
        zgemm3m_("T", "N", x7.size()*x6.size()*x5.size()*x1.size()*x0.size(), c1.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x7.size()*x6.size()*x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<5,0,1,2,3,4,1,1,1,1>(odata_sorted, odata, x7.size(), x6.size(), x5.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, c1, x7, x6, x5, x1, x0);
}

void Task540::Task_local::compute() {
  const Index c1 = b(0);
  const Index x7 = b(1);
  const Index x6 = b(2);
  const Index x5 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I961
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x7, x6, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x7, x6, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x7, x6, x5, x1, x0), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma321
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x7, x2, x6, x5, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x7, x2, x6, x5, x4, x3, x1, x0)]);
        sort_indices<1,4,5,0,2,3,6,7,0,1,1,1>(i0data, i0data_sorted, x7.size(), x2.size(), x6.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, x3, c1, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, x3, c1, x2)]);
        sort_indices<3,0,1,2,0,1,-1,2>(i1data, i1data_sorted, x4.size(), x3.size(), c1.size(), x2.size());
        zgemm3m_("T", "N", x7.size()*x6.size()*x5.size()*x1.size()*x0.size(), c1.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x7.size()*x6.size()*x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<5,0,1,2,3,4,1,1,1,1>(odata_sorted, odata, x7.size(), x6.size(), x5.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, c1, x7, x6, x5, x1, x0);
}

void Task541::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& a3 : *range_[2]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(a3, x2, c1, a2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(a3, x2, c1, a2)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, a3.size(), x2.size(), c1.size(), a2.size());
      // tensor label: I967
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x2, x1, x0)]);
      sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), x2.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c1.size()*a2.size(), x1.size()*x0.size(), a3.size()*x2.size(),
             1.0, i0data_sorted, a3.size()*x2.size(), i1data_sorted, a3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task542::Task_local::compute() {
  const Index a3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I967
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, x2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, x2, x1, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma258
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x2, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x2, x4, x3, x1, x0)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x2.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x5, a3, x4, x3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x5, a3, x4, x3)]);
        sort_indices<0,2,3,1,0,1,1,1>(i1data, i1data_sorted, x5.size(), a3.size(), x4.size(), x3.size());
        zgemm3m_("T", "N", x2.size()*x1.size()*x0.size(), a3.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, x2.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x2.size(), x1.size(), x0.size(), a3.size());
  out()->put_block(odata, a3, x2, x1, x0);
}

void Task543::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& a3 : *range_[2]) {
      // tensor label: v2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(c1, x2, a3, a2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(c1, x2, a3, a2)]);
      sort_indices<1,2,0,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), x2.size(), a3.size(), a2.size());
      // tensor label: I970
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x2, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x2, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), x2.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c1.size()*a2.size(), x1.size()*x0.size(), a3.size()*x2.size(),
             1.0, i0data_sorted, a3.size()*x2.size(), i1data_sorted, a3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task544::Task_local::compute() {
  const Index a3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I970
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, x2, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, x2, x1, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma258
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x2, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x2, x4, x3, x1, x0)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x2.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x5, a3, x4, x3);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x5, a3, x4, x3)]);
        sort_indices<0,2,3,1,0,1,-1,1>(i1data, i1data_sorted, x5.size(), a3.size(), x4.size(), x3.size());
        zgemm3m_("T", "N", x2.size()*x1.size()*x0.size(), a3.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, x2.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x2.size(), x1.size(), x0.size(), a3.size());
  out()->put_block(odata, a3, x2, x1, x0);
}

void Task545::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& a3 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a3, c1, a2);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a3, c1, a2)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), a3.size(), c1.size(), a2.size());
      // tensor label: I1009
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x5, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x5, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), x5.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", c1.size()*a2.size(), x1.size()*x0.size(), a3.size()*x5.size(),
             1.0, i0data_sorted, a3.size()*x5.size(), i1data_sorted, a3.size()*x5.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task546::Task_local::compute() {
  const Index a3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1009
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, x5, x1, x0), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma246
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x3, x2, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x4, x3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x4, x3, x2)]);
        sort_indices<1,2,3,0,0,1,1,2>(i1data, i1data_sorted, a3.size(), x4.size(), x3.size(), x2.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), a3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), a3.size());
  out()->put_block(odata, a3, x5, x1, x0);
}

void Task547::Task_local::compute() {
  const Index a3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1009
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, x5, x1, x0), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma258
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x2, x4, x3, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x2, x4, x3, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x2.size(), x4.size(), x3.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(x4, x3, a3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(x4, x3, a3, x2)]);
        sort_indices<3,0,1,2,0,1,1,2>(i1data, i1data_sorted, x4.size(), x3.size(), a3.size(), x2.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), a3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), a3.size());
  out()->put_block(odata, a3, x5, x1, x0);
}

void Task548::Task_local::compute() {
  const Index c1 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a2 = b(3);
  // tensor label: I112
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(c1, x1, x0, a2);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(c1, x1, x0, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x1, x0, a2), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& a3 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, a2, c1, a3);
      std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, a2, c1, a3)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a2.size(), c1.size(), a3.size());
      // tensor label: I1012
      std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x5, x1, x0);
      std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x5, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), x5.size(), x1.size(), x0.size());
      zgemm3m_("T", "N", a2.size()*c1.size(), x1.size()*x0.size(), a3.size()*x5.size(),
             1.0, i0data_sorted, a3.size()*x5.size(), i1data_sorted, a3.size()*x5.size(),
             1.0, odata_sorted, a2.size()*c1.size());
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x1.size(), x0.size());
  out()->put_block(odata, c1, x1, x0, a2);
}

void Task549::Task_local::compute() {
  const Index a3 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1012
  std::unique_ptr<std::complex<double>[]> odata = out()->move_block(a3, x5, x1, x0);
  std::unique_ptr<std::complex<double>[]> odata_sorted(new std::complex<double>[out()->get_size(a3, x5, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, x5, x1, x0), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      for (auto& x2 : *range_[1]) {
        // tensor label: Gamma246
        std::unique_ptr<std::complex<double>[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
        std::unique_ptr<std::complex<double>[]> i0data_sorted(new std::complex<double>[in(0)->get_size(x5, x4, x3, x2, x1, x0)]);
        sort_indices<1,2,3,0,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
        // tensor label: v2
        std::unique_ptr<std::complex<double>[]> i1data = in(1)->get_block(a3, x4, x3, x2);
        std::unique_ptr<std::complex<double>[]> i1data_sorted(new std::complex<double>[in(1)->get_size(a3, x4, x3, x2)]);
        sort_indices<1,2,3,0,0,1,-1,2>(i1data, i1data_sorted, a3.size(), x4.size(), x3.size(), x2.size());
        zgemm3m_("T", "N", x5.size()*x1.size()*x0.size(), a3.size(), x4.size()*x3.size()*x2.size(),
               1.0, i0data_sorted, x4.size()*x3.size()*x2.size(), i1data_sorted, x4.size()*x3.size()*x2.size(),
               1.0, odata_sorted, x5.size()*x1.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x1.size(), x0.size(), a3.size());
  out()->put_block(odata, a3, x5, x1, x0);
}

#endif

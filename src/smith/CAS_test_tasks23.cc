//
// BAGEL - Parallel electron correlation program.
// Filename: CAS_test_tasks23.cc
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


#include <src/smith/CAS_test_tasks23.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::CAS_test;

void Task1100::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index c1 = b(3);
  const Index c3 = b(4);
  // tensor label: I1201
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x1, c1, c3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, x1, c1, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, x1, c1, c3), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x3, c3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x3, c3, x2)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size(), c3.size(), x2.size());
      // tensor label: I1202
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, x3, x1, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, x3, x1, x2)]);
      sort_indices<4,2,0,1,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), x3.size(), x1.size(), x2.size());
      dgemm_("T", "N", c1.size()*c3.size(), ci0.size()*x0.size()*x1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*c3.size());
    }
  }
  sort_indices<2,3,4,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c3.size(), ci0.size(), x0.size(), x1.size());
  out()->put_block(odata, ci0, x0, x1, c1, c3);
}

void Task1101::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x2 = b(4);
  // tensor label: I1202
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x3, x1, x2);
  {
    // tensor label: Gamma379
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x0, x3, x1, x2);
    sort_indices<0,1,2,3,4,1,1,-1,1>(i0data, odata, ci0.size(), x0.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, ci0, x0, x3, x1, x2);
}

void Task1102::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index c1 = b(3);
  const Index c2 = b(4);
  // tensor label: I1197
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x1, c1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, x1, c1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, x1, c1, c2), 0.0);
  for (auto& x2 : *range_[1]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c2, x2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, x2)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, c2.size(), x2.size());
    // tensor label: I1205
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, x1, x2, c1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, x1, x2, c1)]);
    sort_indices<3,0,1,2,4,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), x1.size(), x2.size(), c1.size());
    dgemm_("T", "N", c2.size(), ci0.size()*x0.size()*x1.size()*c1.size(), x2.size(),
           1.0, i0data_sorted, x2.size(), i1data_sorted, x2.size(),
           1.0, odata_sorted, c2.size());
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c2.size(), ci0.size(), x0.size(), x1.size(), c1.size());
  out()->put_block(odata, ci0, x0, x1, c1, c2);
}

void Task1103::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index x2 = b(3);
  const Index c1 = b(4);
  // tensor label: I1205
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x1, x2, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, x1, x2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, x1, x2, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, c1, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, c1, x3)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c1.size(), x3.size());
        // tensor label: I1206
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x5, x4, x0, x3, x1, x2);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x5, x4, x0, x3, x1, x2)]);
        sort_indices<4,2,1,0,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x5.size(), x4.size(), x0.size(), x3.size(), x1.size(), x2.size());
        dgemm_("T", "N", c1.size(), ci0.size()*x0.size()*x1.size()*x2.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x0.size(), x1.size(), x2.size());
  out()->put_block(odata, ci0, x0, x1, x2, c1);
}

void Task1104::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x5 = b(1);
  const Index x4 = b(2);
  const Index x0 = b(3);
  const Index x3 = b(4);
  const Index x1 = b(5);
  const Index x2 = b(6);
  // tensor label: I1206
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x5, x4, x0, x3, x1, x2);
  {
    // tensor label: Gamma380
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x5, x4, x0, x3, x1, x2);
    sort_indices<0,1,2,3,4,5,6,1,1,1,2>(i0data, odata, ci0.size(), x5.size(), x4.size(), x0.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, ci0, x5, x4, x0, x3, x1, x2);
}

void Task1105::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index c1 = b(3);
  const Index c2 = b(4);
  // tensor label: I1197
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x1, c1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, x1, c1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, x1, c1, c2), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& a3 : *range_[2]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(a3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a3, x2)]);
      sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, a3.size(), x2.size());
      // tensor label: I1209
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x1, x0, x2, c1, a3, c2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x1, x0, x2, c1, a3, c2)]);
      sort_indices<3,5,0,1,2,4,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x1.size(), x0.size(), x2.size(), c1.size(), a3.size(), c2.size());
      dgemm_("T", "N", 1, ci0.size()*x1.size()*x0.size()*c1.size()*c2.size(), x2.size()*a3.size(),
             1.0, i0data_sorted, x2.size()*a3.size(), i1data_sorted, x2.size()*a3.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,2,1,3,4,1,1,1,1>(odata_sorted, odata, ci0.size(), x1.size(), x0.size(), c1.size(), c2.size());
  out()->put_block(odata, ci0, x0, x1, c1, c2);
}

void Task1106::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index x2 = b(3);
  const Index c1 = b(4);
  const Index a3 = b(5);
  const Index c2 = b(6);
  // tensor label: I1209
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x1, x0, x2, c1, a3, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x1, x0, x2, c1, a3, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x1, x0, x2, c1, a3, c2), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a3, c2, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a3, c2, x3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a3.size(), c2.size(), x3.size());
    // tensor label: I1210
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x1, x3, x0, x2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x1, x3, x0, x2)]);
    sort_indices<2,0,1,3,4,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x1.size(), x3.size(), x0.size(), x2.size());
    dgemm_("T", "N", c1.size()*a3.size()*c2.size(), ci0.size()*x1.size()*x0.size()*x2.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c1.size()*a3.size()*c2.size());
  }
  sort_indices<3,4,5,6,0,1,2,1,1,1,1>(odata_sorted, odata, c1.size(), a3.size(), c2.size(), ci0.size(), x1.size(), x0.size(), x2.size());
  out()->put_block(odata, ci0, x1, x0, x2, c1, a3, c2);
}

void Task1107::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x0 = b(3);
  const Index x2 = b(4);
  // tensor label: I1210
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x1, x3, x0, x2);
  {
    // tensor label: Gamma381
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x1, x3, x0, x2);
    sort_indices<0,1,2,3,4,1,1,-1,2>(i0data, odata, ci0.size(), x1.size(), x3.size(), x0.size(), x2.size());
  }
  out()->put_block(odata, ci0, x1, x3, x0, x2);
}

void Task1108::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index c1 = b(3);
  const Index c2 = b(4);
  // tensor label: I1197
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x1, c1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, x1, c1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, x1, c1, c2), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x3, c2, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x3, c2, x2)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size(), c2.size(), x2.size());
      // tensor label: I1922
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, x3, x1, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, x3, x1, x2)]);
      sort_indices<4,2,0,1,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), x3.size(), x1.size(), x2.size());
      dgemm_("T", "N", c1.size()*c2.size(), ci0.size()*x0.size()*x1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*c2.size());
    }
  }
  sort_indices<2,3,4,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c2.size(), ci0.size(), x0.size(), x1.size());
  out()->put_block(odata, ci0, x0, x1, c1, c2);
}

void Task1109::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x2 = b(4);
  // tensor label: I1922
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x3, x1, x2);
  {
    // tensor label: Gamma379
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x0, x3, x1, x2);
    dscal_(ci0.size()*x0.size()*x3.size()*x1.size()*x2.size(), e0_, i0data.get(), 1);
    sort_indices<0,1,2,3,4,1,1,-1,2>(i0data, odata, ci0.size(), x0.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, ci0, x0, x3, x1, x2);
}

void Task1110::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index c1 = b(3);
  const Index c2 = b(4);
  // tensor label: I1197
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x1, c1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, x1, c1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, x1, c1, c2), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: v2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x3, c2, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x3, c2, x2)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size(), c2.size(), x2.size());
      // tensor label: I1994
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, x3, x1, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, x3, x1, x2)]);
      sort_indices<4,2,0,1,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), x3.size(), x1.size(), x2.size());
      dgemm_("T", "N", c1.size()*c2.size(), ci0.size()*x0.size()*x1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*c2.size());
    }
  }
  sort_indices<2,3,4,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c2.size(), ci0.size(), x0.size(), x1.size());
  out()->put_block(odata, ci0, x0, x1, c1, c2);
}

void Task1111::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x2 = b(4);
  // tensor label: I1994
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, x3, x1, x2);
  {
    // tensor label: Gamma379
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x0, x3, x1, x2);
    sort_indices<0,1,2,3,4,1,1,1,1>(i0data, odata, ci0.size(), x0.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, ci0, x0, x3, x1, x2);
}

void Task1112::Task_local::compute() {
  const Index ci0 = b(0);
  // tensor label: I1196
  std::unique_ptr<double[]> odata = out()->move_block(ci0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& x1 : *range_[1]) {
      for (auto& c1 : *range_[0]) {
        for (auto& x2 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1, c1, x2);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1, c1, x2)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size(), c1.size(), x2.size());
          // tensor label: I1212
          std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x1, x0, c1);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x1, x0, c1)]);
          sort_indices<3,2,4,1,0,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x1.size(), x0.size(), c1.size());
          dgemm_("T", "N", 1, ci0.size(), x2.size()*x1.size()*x0.size()*c1.size(),
                 1.0, i0data_sorted, x2.size()*x1.size()*x0.size()*c1.size(), i1data_sorted, x2.size()*x1.size()*x0.size()*c1.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1>(odata_sorted, odata, ci0.size());
  out()->put_block(odata, ci0);
}

void Task1113::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& c2 : *range_[0]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, c2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, c2)]);
      sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x3.size(), c2.size());
      // tensor label: I1213
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x3, x1, x0, c1, c2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x3, x1, x0, c1, c2)]);
      sort_indices<6,2,0,1,3,4,5,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size(), c1.size(), c2.size());
      dgemm_("T", "N", 1, ci0.size()*x2.size()*x1.size()*x0.size()*c1.size(), x3.size()*c2.size(),
             1.0, i0data_sorted, x3.size()*c2.size(), i1data_sorted, x3.size()*c2.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,2,3,4,1,1,1,1>(odata_sorted, odata, ci0.size(), x2.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1114::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x0 = b(4);
  const Index c1 = b(5);
  const Index c2 = b(6);
  // tensor label: I1213
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x3, x1, x0, c1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x3, x1, x0, c1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x3, x1, x0, c1, c2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x5, c2, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x5, c2, x4)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x5.size(), c2.size(), x4.size());
      // tensor label: I1214
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x5, x3, x4, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x5, x3, x4, x1, x0)]);
      sort_indices<4,2,0,1,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x5.size(), x3.size(), x4.size(), x1.size(), x0.size());
      dgemm_("T", "N", c1.size()*c2.size(), ci0.size()*x2.size()*x3.size()*x1.size()*x0.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, c1.size()*c2.size());
    }
  }
  sort_indices<2,3,4,5,6,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c2.size(), ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x3, x1, x0, c1, c2);
}

void Task1115::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x5 = b(2);
  const Index x3 = b(3);
  const Index x4 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1214
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x5, x3, x4, x1, x0);
  {
    // tensor label: Gamma382
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x2, x5, x3, x4, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,1,2>(i0data, odata, ci0.size(), x2.size(), x5.size(), x3.size(), x4.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x2, x5, x3, x4, x1, x0);
}

void Task1116::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x6 : *range_[1]) {
      for (auto& x7 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x7, x6, c1, x5);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x7, x6, c1, x5)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x7.size(), x6.size(), c1.size(), x5.size());
        // tensor label: I1217
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x7, x6, x2, x5, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x7, x6, x2, x5, x1, x0)]);
        sort_indices<4,2,1,0,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x7.size(), x6.size(), x2.size(), x5.size(), x1.size(), x0.size());
        dgemm_("T", "N", c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x7.size()*x6.size()*x5.size(),
               1.0, i0data_sorted, x7.size()*x6.size()*x5.size(), i1data_sorted, x7.size()*x6.size()*x5.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1117::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x7 = b(1);
  const Index x6 = b(2);
  const Index x2 = b(3);
  const Index x5 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1217
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x7, x6, x2, x5, x1, x0);
  {
    // tensor label: Gamma383
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x7, x6, x2, x5, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,1,4>(i0data, odata, ci0.size(), x7.size(), x6.size(), x2.size(), x5.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x7, x6, x2, x5, x1, x0);
}

void Task1118::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& c2 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, c2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, c2)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, c1.size(), c2.size());
    // tensor label: I1220
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x1, x0, c2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x1, x0, c2)]);
    sort_indices<4,0,1,2,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x1.size(), x0.size(), c2.size());
    dgemm_("T", "N", c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), c2.size(),
           1.0, i0data_sorted, c2.size(), i1data_sorted, c2.size(),
           1.0, odata_sorted, c1.size());
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1119::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c2 = b(4);
  // tensor label: I1220
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c2), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, c2, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, c2, x3)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c2.size(), x3.size());
        // tensor label: I1221
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x5, x4, x2, x3, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x5, x4, x2, x3, x1, x0)]);
        sort_indices<4,2,1,0,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
        dgemm_("T", "N", c2.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c2.size());
      }
    }
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c2.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c2);
}

void Task1120::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x5 = b(1);
  const Index x4 = b(2);
  const Index x2 = b(3);
  const Index x3 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1221
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x5, x4, x2, x3, x1, x0);
  {
    // tensor label: Gamma384
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x5, x4, x2, x3, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,-1,4>(i0data, odata, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x5, x4, x2, x3, x1, x0);
}

void Task1121::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& c2 : *range_[0]) {
    for (auto& a3 : *range_[2]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(a3, c2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a3, c2)]);
      sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, a3.size(), c2.size());
      // tensor label: I1224
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x1, x0, c2, a3, c1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x1, x0, c2, a3, c1)]);
      sort_indices<4,5,0,1,2,3,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x1.size(), x0.size(), c2.size(), a3.size(), c1.size());
      dgemm_("T", "N", 1, ci0.size()*x2.size()*x1.size()*x0.size()*c1.size(), c2.size()*a3.size(),
             1.0, i0data_sorted, c2.size()*a3.size(), i1data_sorted, c2.size()*a3.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,2,3,4,1,1,1,1>(odata_sorted, odata, ci0.size(), x2.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1122::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c2 = b(4);
  const Index a3 = b(5);
  const Index c1 = b(6);
  // tensor label: I1224
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c2, a3, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c2, a3, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c2, a3, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c2, a3, c1, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, a3, c1, x3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c2.size(), a3.size(), c1.size(), x3.size());
    // tensor label: I1225
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x3, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x3, x1, x0)]);
    sort_indices<2,0,1,3,4,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
    dgemm_("T", "N", c2.size()*a3.size()*c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c2.size()*a3.size()*c1.size());
  }
  sort_indices<3,4,5,6,0,1,2,1,1,1,1>(odata_sorted, odata, c2.size(), a3.size(), c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c2, a3, c1);
}

void Task1123::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x0 = b(4);
  // tensor label: I1225
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x3, x1, x0);
  {
    // tensor label: Gamma385
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x2, x3, x1, x0);
    sort_indices<0,1,2,3,4,1,1,1,2>(i0data, odata, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x2, x3, x1, x0);
}

void Task1124::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c2 = b(4);
  const Index a3 = b(5);
  const Index c1 = b(6);
  // tensor label: I1224
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c2, a3, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c2, a3, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c2, a3, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a3, c2, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a3, c2, x3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a3.size(), c2.size(), x3.size());
    // tensor label: I1229
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x3, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x3, x1, x0)]);
    sort_indices<2,0,1,3,4,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
    dgemm_("T", "N", c1.size()*a3.size()*c2.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c1.size()*a3.size()*c2.size());
  }
  sort_indices<3,4,5,6,2,1,0,1,1,1,1>(odata_sorted, odata, c1.size(), a3.size(), c2.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c2, a3, c1);
}

void Task1125::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x0 = b(4);
  // tensor label: I1229
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x3, x1, x0);
  {
    // tensor label: Gamma385
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x2, x3, x1, x0);
    sort_indices<0,1,2,3,4,1,1,-1,4>(i0data, odata, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x2, x3, x1, x0);
}

void Task1126::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& a2 : *range_[2]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(a2, x3);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a2, x3)]);
      sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, a2.size(), x3.size());
      // tensor label: I1232
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x3, x2, x1, x0, a2, c1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x3, x2, x1, x0, a2, c1)]);
      sort_indices<1,5,0,2,3,4,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x3.size(), x2.size(), x1.size(), x0.size(), a2.size(), c1.size());
      dgemm_("T", "N", 1, ci0.size()*x2.size()*x1.size()*x0.size()*c1.size(), x3.size()*a2.size(),
             1.0, i0data_sorted, x3.size()*a2.size(), i1data_sorted, x3.size()*a2.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,2,3,4,1,1,1,1>(odata_sorted, odata, ci0.size(), x2.size(), x1.size(), x0.size(), c1.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1127::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  const Index x0 = b(4);
  const Index a2 = b(5);
  const Index c1 = b(6);
  // tensor label: I1232
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x3, x2, x1, x0, a2, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x3, x2, x1, x0, a2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x3, x2, x1, x0, a2, c1), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x5, a2, c1, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, a2, c1, x4)]);
      sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a2.size(), c1.size(), x4.size());
      // tensor label: I1233
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x5, x3, x2, x4, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x5, x3, x2, x4, x1, x0)]);
      sort_indices<4,1,0,2,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x5.size(), x3.size(), x2.size(), x4.size(), x1.size(), x0.size());
      dgemm_("T", "N", a2.size()*c1.size(), ci0.size()*x3.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, a2.size()*c1.size());
    }
  }
  sort_indices<2,3,4,5,6,0,1,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), ci0.size(), x3.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x3, x2, x1, x0, a2, c1);
}

void Task1128::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x5 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index x4 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1233
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x5, x3, x2, x4, x1, x0);
  {
    // tensor label: Gamma387
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x5, x3, x2, x4, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,-1,4>(i0data, odata, ci0.size(), x5.size(), x3.size(), x2.size(), x4.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x5, x3, x2, x4, x1, x0);
}

void Task1129::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  const Index x0 = b(4);
  const Index a2 = b(5);
  const Index c1 = b(6);
  // tensor label: I1232
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x3, x2, x1, x0, a2, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x3, x2, x1, x0, a2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x3, x2, x1, x0, a2, c1), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, x5, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, x5, x4)]);
      sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), x5.size(), x4.size());
      // tensor label: I1237
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x5, x4, x2, x3, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x5, x4, x2, x3, x1, x0)]);
      sort_indices<2,1,0,3,4,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
      dgemm_("T", "N", c1.size()*a2.size(), ci0.size()*x2.size()*x3.size()*x1.size()*x0.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<2,4,3,5,6,1,0,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x3, x2, x1, x0, a2, c1);
}

void Task1130::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x5 = b(1);
  const Index x4 = b(2);
  const Index x2 = b(3);
  const Index x3 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1237
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x5, x4, x2, x3, x1, x0);
  {
    // tensor label: Gamma384
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x5, x4, x2, x3, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,1,4>(i0data, odata, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x5, x4, x2, x3, x1, x0);
}

void Task1131::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, c1, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, c1, x3)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c1.size(), x3.size());
        // tensor label: I1925
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x5, x4, x2, x3, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x5, x4, x2, x3, x1, x0)]);
        sort_indices<4,2,1,0,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
        dgemm_("T", "N", c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1132::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x5 = b(1);
  const Index x4 = b(2);
  const Index x2 = b(3);
  const Index x3 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1925
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x5, x4, x2, x3, x1, x0);
  {
    // tensor label: Gamma384
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x5, x4, x2, x3, x1, x0);
    dscal_(ci0.size()*x5.size()*x4.size()*x2.size()*x3.size()*x1.size()*x0.size(), e0_, i0data.get(), 1);
    sort_indices<0,1,2,3,4,5,6,1,1,-1,4>(i0data, odata, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x5, x4, x2, x3, x1, x0);
}

void Task1133::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: v2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x5, x4, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x5, x4, x3)]);
        sort_indices<3,2,1,0,0,1,1,1>(i0data, i0data_sorted, c1.size(), x5.size(), x4.size(), x3.size());
        // tensor label: I1997
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x5, x4, x3, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x5, x4, x3, x1, x0)]);
        sort_indices<4,3,2,0,1,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
        dgemm_("T", "N", c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1134::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x5 = b(2);
  const Index x4 = b(3);
  const Index x3 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I1997
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x5, x4, x3, x1, x0);
  {
    // tensor label: Gamma591
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x2, x5, x4, x3, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,1,2>(i0data, odata, ci0.size(), x2.size(), x5.size(), x4.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x2, x5, x4, x3, x1, x0);
}

void Task1135::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: v2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, c1, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, c1, x3)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c1.size(), x3.size());
        // tensor label: I2000
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x5, x4, x2, x3, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x5, x4, x2, x3, x1, x0)]);
        sort_indices<4,2,1,0,3,5,6,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
        dgemm_("T", "N", c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1136::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x5 = b(1);
  const Index x4 = b(2);
  const Index x2 = b(3);
  const Index x3 = b(4);
  const Index x1 = b(5);
  const Index x0 = b(6);
  // tensor label: I2000
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x5, x4, x2, x3, x1, x0);
  {
    // tensor label: Gamma384
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x5, x4, x2, x3, x1, x0);
    sort_indices<0,1,2,3,4,5,6,1,1,1,2>(i0data, odata, ci0.size(), x5.size(), x4.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x5, x4, x2, x3, x1, x0);
}

void Task1137::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index c1 = b(4);
  // tensor label: I1212
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x1, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x2, x1, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x2, x1, x0, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: h1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x3)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size());
    // tensor label: I2102
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x2, x3, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x2, x3, x1, x0)]);
    sort_indices<2,0,1,3,4,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
    dgemm_("T", "N", c1.size(), ci0.size()*x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c1.size());
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x2, x1, x0, c1);
}

void Task1138::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x2 = b(1);
  const Index x3 = b(2);
  const Index x1 = b(3);
  const Index x0 = b(4);
  // tensor label: I2102
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x2, x3, x1, x0);
  {
    // tensor label: Gamma385
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x2, x3, x1, x0);
    sort_indices<0,1,2,3,4,1,1,1,1>(i0data, odata, ci0.size(), x2.size(), x3.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, ci0, x2, x3, x1, x0);
}

void Task1139::Task_local::compute() {
  const Index ci0 = b(0);
  // tensor label: I1196
  std::unique_ptr<double[]> odata = out()->move_block(ci0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c3 : *range_[0]) {
        for (auto& x0 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
          // tensor label: I1239
          std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, c1, c3, a2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, c1, c3, a2)]);
          sort_indices<2,4,3,1,0,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), c1.size(), c3.size(), a2.size());
          dgemm_("T", "N", 1, ci0.size(), x0.size()*c1.size()*c3.size()*a2.size(),
                 1.0, i0data_sorted, x0.size()*c1.size()*c3.size()*a2.size(), i1data_sorted, x0.size()*c1.size()*c3.size()*a2.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1>(odata_sorted, odata, ci0.size());
  out()->put_block(odata, ci0);
}

void Task1140::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index c1 = b(2);
  const Index c3 = b(3);
  const Index a2 = b(4);
  // tensor label: I1239
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, c1, c3, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, c1, c3, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, c1, c3, a2), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, a2)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), a2.size());
    // tensor label: I1240
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x1, x0, c1, c3);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x1, x0, c1, c3)]);
    sort_indices<1,0,2,3,4,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x1.size(), x0.size(), c1.size(), c3.size());
    dgemm_("T", "N", a2.size(), ci0.size()*x0.size()*c1.size()*c3.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, a2.size());
  }
  sort_indices<1,2,3,4,0,1,1,1,1>(odata_sorted, odata, a2.size(), ci0.size(), x0.size(), c1.size(), c3.size());
  out()->put_block(odata, ci0, x0, c1, c3, a2);
}

void Task1141::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index c1 = b(3);
  const Index c3 = b(4);
  // tensor label: I1240
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x1, x0, c1, c3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x1, x0, c1, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x1, x0, c1, c3), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x3, c3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x3, c3, x2)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size(), c3.size(), x2.size());
      // tensor label: I1241
      std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x1, x3, x0, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x1, x3, x0, x2)]);
      sort_indices<4,2,0,1,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x1.size(), x3.size(), x0.size(), x2.size());
      dgemm_("T", "N", c1.size()*c3.size(), ci0.size()*x1.size()*x0.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*c3.size());
    }
  }
  sort_indices<2,3,4,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c3.size(), ci0.size(), x1.size(), x0.size());
  out()->put_block(odata, ci0, x1, x0, c1, c3);
}

void Task1142::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x0 = b(3);
  const Index x2 = b(4);
  // tensor label: I1241
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x1, x3, x0, x2);
  {
    // tensor label: Gamma381
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x1, x3, x0, x2);
    sort_indices<0,1,2,3,4,1,1,-1,2>(i0data, odata, ci0.size(), x1.size(), x3.size(), x0.size(), x2.size());
  }
  out()->put_block(odata, ci0, x1, x3, x0, x2);
}

void Task1143::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index c1 = b(2);
  const Index c3 = b(3);
  const Index a2 = b(4);
  // tensor label: I1239
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, c1, c3, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, c1, c3, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, c1, c3, a2), 0.0);
  // tensor label: f1
  std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size());
  // tensor label: I1244
  std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, c3);
  std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, c3)]);
  sort_indices<0,1,2,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), c3.size());
  dgemm_("T", "N", c1.size()*a2.size(), ci0.size()*x0.size()*c3.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c1.size()*a2.size());
  sort_indices<2,3,0,4,1,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), ci0.size(), x0.size(), c3.size());
  out()->put_block(odata, ci0, x0, c1, c3, a2);
}

void Task1144::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index c3 = b(2);
  // tensor label: I1244
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, c3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, c3), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, c3, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, c3, x1)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), c3.size(), x1.size());
        // tensor label: I1245
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x3, x2, x0, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x3, x2, x0, x1)]);
        sort_indices<4,2,1,0,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x3.size(), x2.size(), x0.size(), x1.size());
        dgemm_("T", "N", c3.size(), ci0.size()*x0.size(), x3.size()*x2.size()*x1.size(),
               1.0, i0data_sorted, x3.size()*x2.size()*x1.size(), i1data_sorted, x3.size()*x2.size()*x1.size(),
               1.0, odata_sorted, c3.size());
      }
    }
  }
  sort_indices<1,2,0,1,1,1,1>(odata_sorted, odata, c3.size(), ci0.size(), x0.size());
  out()->put_block(odata, ci0, x0, c3);
}

void Task1145::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x0 = b(3);
  const Index x1 = b(4);
  // tensor label: I1245
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x3, x2, x0, x1);
  {
    // tensor label: Gamma390
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x3, x2, x0, x1);
    sort_indices<0,1,2,3,4,1,1,1,2>(i0data, odata, ci0.size(), x3.size(), x2.size(), x0.size(), x1.size());
  }
  out()->put_block(odata, ci0, x3, x2, x0, x1);
}

void Task1146::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index c1 = b(2);
  const Index c3 = b(3);
  const Index a2 = b(4);
  // tensor label: I1239
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, c1, c3, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, c1, c3, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, c1, c3, a2), 0.0);
  // tensor label: f1
  std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size());
  // tensor label: I1248
  std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, c1);
  std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, c1)]);
  sort_indices<0,1,2,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), c1.size());
  dgemm_("T", "N", c3.size()*a2.size(), ci0.size()*x0.size()*c1.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c3.size()*a2.size());
  sort_indices<2,3,4,0,1,1,1,1,1>(odata_sorted, odata, c3.size(), a2.size(), ci0.size(), x0.size(), c1.size());
  out()->put_block(odata, ci0, x0, c1, c3, a2);
}

void Task1147::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index c1 = b(2);
  // tensor label: I1248
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, c1), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, c1, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, c1, x1)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), c1.size(), x1.size());
        // tensor label: I1249
        std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x3, x2, x0, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x3, x2, x0, x1)]);
        sort_indices<4,2,1,0,3,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x3.size(), x2.size(), x0.size(), x1.size());
        dgemm_("T", "N", c1.size(), ci0.size()*x0.size(), x3.size()*x2.size()*x1.size(),
               1.0, i0data_sorted, x3.size()*x2.size()*x1.size(), i1data_sorted, x3.size()*x2.size()*x1.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,0,1,1,1,1>(odata_sorted, odata, c1.size(), ci0.size(), x0.size());
  out()->put_block(odata, ci0, x0, c1);
}

void Task1148::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x0 = b(3);
  const Index x1 = b(4);
  // tensor label: I1249
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x3, x2, x0, x1);
  {
    // tensor label: Gamma390
    std::unique_ptr<double[]> i0data = in(0)->get_block(ci0, x3, x2, x0, x1);
    sort_indices<0,1,2,3,4,1,1,-1,4>(i0data, odata, ci0.size(), x3.size(), x2.size(), x0.size(), x1.size());
  }
  out()->put_block(odata, ci0, x3, x2, x0, x1);
}

void Task1149::Task_local::compute() {
  const Index ci0 = b(0);
  const Index x0 = b(1);
  const Index c1 = b(2);
  const Index c3 = b(3);
  const Index a2 = b(4);
  // tensor label: I1239
  std::unique_ptr<double[]> odata = out()->move_block(ci0, x0, c1, c3, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(ci0, x0, c1, c3, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(ci0, x0, c1, c3, a2), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, c1, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2, c1, x3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), c1.size(), x3.size());
    // tensor label: I1252
    std::unique_ptr<double[]> i1data = in(1)->get_block(ci0, x0, x3);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(ci0, x0, x3)]);
    sort_indices<2,0,1,0,1,1,1>(i1data, i1data_sorted, ci0.size(), x0.size(), x3.size());
    dgemm_("T", "N", c3.size()*a2.size()*c1.size(), ci0.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c3.size()*a2.size()*c1.size());
  }
  sort_indices<3,4,2,0,1,1,1,1,1>(odata_sorted, odata, c3.size(), a2.size(), c1.size(), ci0.size(), x0.size());
  out()->put_block(odata, ci0, x0, c1, c3, a2);
}


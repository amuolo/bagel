//
// BAGEL - Parallel electron correlation program.
// Filename: CAS_test_tasks16.cc
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


#include <src/smith/CAS_test_tasks16.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::CAS_test;

void Task751::Task_local::compute() {
  const Index x2 = b(0);
  const Index x3 = b(1);
  // tensor label: den2
  std::unique_ptr<double[]> odata = out()->move_block(x2, x3);
  {
    // tensor label: I872
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2);
    sort_indices<1,0,1,1,1,1>(i0data, odata, x3.size(), x2.size());
  }
  out()->put_block(odata, x2, x3);
}

void Task752::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  // tensor label: I872
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& x0 : *range_[1]) {
      for (auto& c2 : *range_[0]) {
        for (auto& x1 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0, c2, x1);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0, c2, x1)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size(), c2.size(), x1.size());
          // tensor label: I873
          std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, x3, x2, c1, c2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, x3, x2, c1, c2)]);
          sort_indices<4,0,5,1,2,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), x3.size(), x2.size(), c1.size(), c2.size());
          dgemm_("T", "N", 1, x3.size()*x2.size(), x0.size()*x1.size()*c1.size()*c2.size(),
                 1.0, i0data_sorted, x0.size()*x1.size()*c1.size()*c2.size(), i1data_sorted, x0.size()*x1.size()*c1.size()*c2.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size());
  out()->put_block(odata, x3, x2);
}

void Task753::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index c1 = b(4);
  const Index c2 = b(5);
  // tensor label: I873
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, x3, x2, c1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x3, x2, c1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x3, x2, c1, c2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x5, c2, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x5, c2, x4)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x5.size(), c2.size(), x4.size());
      // tensor label: I874
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x5, x1, x4, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x5, x1, x4, x3, x2)]);
      sort_indices<3,1,0,2,4,5,0,1,1,1>(i1data, i1data_sorted, x0.size(), x5.size(), x1.size(), x4.size(), x3.size(), x2.size());
      dgemm_("T", "N", c1.size()*c2.size(), x0.size()*x1.size()*x3.size()*x2.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, c1.size()*c2.size());
    }
  }
  sort_indices<2,3,4,5,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c2.size(), x0.size(), x1.size(), x3.size(), x2.size());
  out()->put_block(odata, x0, x1, x3, x2, c1, c2);
}

void Task754::Task_local::compute() {
  const Index x0 = b(0);
  const Index x5 = b(1);
  const Index x1 = b(2);
  const Index x4 = b(3);
  const Index x3 = b(4);
  const Index x2 = b(5);
  // tensor label: I874
  std::unique_ptr<double[]> odata = out()->move_block(x0, x5, x1, x4, x3, x2);
  {
    // tensor label: Gamma268
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x5, x1, x4, x3, x2);
    sort_indices<0,1,2,3,4,5,1,1,1,2>(i0data, odata, x0.size(), x5.size(), x1.size(), x4.size(), x3.size(), x2.size());
  }
  out()->put_block(odata, x0, x5, x1, x4, x3, x2);
}

void Task755::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  // tensor label: I872
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& a1 : *range_[2]) {
      for (auto& c2 : *range_[0]) {
        for (auto& x1 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, c2, x1);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, c2, x1)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
          // tensor label: I966
          std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, x3, x2, a1, c2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, x3, x2, a1, c2)]);
          sort_indices<0,4,5,1,2,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), x3.size(), x2.size(), a1.size(), c2.size());
          dgemm_("T", "N", 1, x3.size()*x2.size(), x0.size()*x1.size()*a1.size()*c2.size(),
                 1.0, i0data_sorted, x0.size()*x1.size()*a1.size()*c2.size(), i1data_sorted, x0.size()*x1.size()*a1.size()*c2.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size());
  out()->put_block(odata, x3, x2);
}

void Task756::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index a1 = b(4);
  const Index c2 = b(5);
  // tensor label: I966
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, x3, x2, a1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x3, x2, a1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x3, x2, a1, c2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x5, a1, c2, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, a1, c2, x4)]);
      sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a1.size(), c2.size(), x4.size());
      // tensor label: I967
      std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x0, x1, x4, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x0, x1, x4, x3, x2)]);
      sort_indices<3,0,1,2,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x0.size(), x1.size(), x4.size(), x3.size(), x2.size());
      dgemm_("T", "N", a1.size()*c2.size(), x0.size()*x1.size()*x3.size()*x2.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, a1.size()*c2.size());
    }
  }
  sort_indices<2,3,4,5,0,1,1,1,1,1>(odata_sorted, odata, a1.size(), c2.size(), x0.size(), x1.size(), x3.size(), x2.size());
  out()->put_block(odata, x0, x1, x3, x2, a1, c2);
}

void Task757::Task_local::compute() {
  const Index x5 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index x4 = b(3);
  const Index x3 = b(4);
  const Index x2 = b(5);
  // tensor label: I967
  std::unique_ptr<double[]> odata = out()->move_block(x5, x0, x1, x4, x3, x2);
  {
    // tensor label: Gamma299
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x0, x1, x4, x3, x2);
    sort_indices<0,1,2,3,4,5,1,1,1,4>(i0data, odata, x5.size(), x0.size(), x1.size(), x4.size(), x3.size(), x2.size());
  }
  out()->put_block(odata, x5, x0, x1, x4, x3, x2);
}

void Task758::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index a1 = b(4);
  const Index c2 = b(5);
  // tensor label: I966
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, x3, x2, a1, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x3, x2, a1, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x3, x2, a1, c2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c2, a1, x5, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, a1, x5, x4)]);
      sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c2.size(), a1.size(), x5.size(), x4.size());
      // tensor label: I976
      std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x4, x3, x2, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x4, x3, x2, x1, x0)]);
      sort_indices<1,0,2,3,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
      dgemm_("T", "N", c2.size()*a1.size(), x3.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, c2.size()*a1.size());
    }
  }
  sort_indices<5,4,2,3,1,0,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), x3.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x0, x1, x3, x2, a1, c2);
}

void Task759::Task_local::compute() {
  const Index x5 = b(0);
  const Index x4 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I976
  std::unique_ptr<double[]> odata = out()->move_block(x5, x4, x3, x2, x1, x0);
  {
    // tensor label: Gamma302
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
    sort_indices<0,1,2,3,4,5,1,1,-1,4>(i0data, odata, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x5, x4, x3, x2, x1, x0);
}

void Task760::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  // tensor label: I872
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& x0 : *range_[1]) {
        for (auto& x1 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, x0, x1);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, x0, x1)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), x0.size(), x1.size());
          // tensor label: I1008
          std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, x1, x0, a2, c1);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, x1, x0, a2, c1)]);
          sort_indices<5,4,3,2,0,1,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size(), a2.size(), c1.size());
          dgemm_("T", "N", 1, x3.size()*x2.size(), x1.size()*x0.size()*a2.size()*c1.size(),
                 1.0, i0data_sorted, x1.size()*x0.size()*a2.size()*c1.size(), i1data_sorted, x1.size()*x0.size()*a2.size()*c1.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size());
  out()->put_block(odata, x3, x2);
}

void Task761::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index a2 = b(4);
  const Index c1 = b(5);
  // tensor label: I1008
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2, x1, x0, a2, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2, x1, x0, a2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2, x1, x0, a2, c1), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x5, a2, c1, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, a2, c1, x4)]);
      sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), a2.size(), c1.size(), x4.size());
      // tensor label: I1009
      std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x4, x3, x2, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x4, x3, x2, x1, x0)]);
      sort_indices<1,0,2,3,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
      dgemm_("T", "N", a2.size()*c1.size(), x3.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, a2.size()*c1.size());
    }
  }
  sort_indices<2,3,4,5,0,1,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), x3.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x3, x2, x1, x0, a2, c1);
}

void Task762::Task_local::compute() {
  const Index x5 = b(0);
  const Index x4 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I1009
  std::unique_ptr<double[]> odata = out()->move_block(x5, x4, x3, x2, x1, x0);
  {
    // tensor label: Gamma302
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
    sort_indices<0,1,2,3,4,5,1,1,-1,4>(i0data, odata, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x5, x4, x3, x2, x1, x0);
}

void Task763::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  const Index a2 = b(4);
  const Index c1 = b(5);
  // tensor label: I1008
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2, x1, x0, a2, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2, x1, x0, a2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2, x1, x0, a2, c1), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, x5, x4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, x5, x4)]);
      sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), x5.size(), x4.size());
      // tensor label: I1018
      std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x4, x3, x2, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x4, x3, x2, x1, x0)]);
      sort_indices<1,0,2,3,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
      dgemm_("T", "N", c1.size()*a2.size(), x3.size()*x2.size()*x1.size()*x0.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, c1.size()*a2.size());
    }
  }
  sort_indices<2,3,4,5,1,0,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), x3.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x3, x2, x1, x0, a2, c1);
}

void Task764::Task_local::compute() {
  const Index x5 = b(0);
  const Index x4 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index x1 = b(4);
  const Index x0 = b(5);
  // tensor label: I1018
  std::unique_ptr<double[]> odata = out()->move_block(x5, x4, x3, x2, x1, x0);
  {
    // tensor label: Gamma302
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, x3, x2, x1, x0);
    sort_indices<0,1,2,3,4,5,1,1,1,2>(i0data, odata, x5.size(), x4.size(), x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x5, x4, x3, x2, x1, x0);
}

void Task765::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  // tensor label: I872
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& a1 : *range_[2]) {
      for (auto& x1 : *range_[1]) {
        for (auto& a2 : *range_[2]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, x1, a2);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, x1, a2)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), x1.size(), a2.size());
          // tensor label: I1157
          std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, x3, x2, a1, a2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, x3, x2, a1, a2)]);
          sort_indices<0,4,1,5,2,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), x3.size(), x2.size(), a1.size(), a2.size());
          dgemm_("T", "N", 1, x3.size()*x2.size(), x0.size()*x1.size()*a1.size()*a2.size(),
                 1.0, i0data_sorted, x0.size()*x1.size()*a1.size()*a2.size(), i1data_sorted, x0.size()*x1.size()*a1.size()*a2.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size());
  out()->put_block(odata, x3, x2);
}

void Task766::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  const Index a1 = b(4);
  const Index a2 = b(5);
  // tensor label: I1157
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, x3, x2, a1, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x3, x2, a1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x3, x2, a1, a2), 0.0);
  for (auto& x4 : *range_[1]) {
    for (auto& x5 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x5, a1, x4, a2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, a1, x4, a2)]);
      sort_indices<2,0,1,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), a1.size(), x4.size(), a2.size());
      // tensor label: I1158
      std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x0, x4, x1, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x0, x4, x1, x3, x2)]);
      sort_indices<2,0,1,3,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x0.size(), x4.size(), x1.size(), x3.size(), x2.size());
      dgemm_("T", "N", a1.size()*a2.size(), x0.size()*x1.size()*x3.size()*x2.size(), x5.size()*x4.size(),
             1.0, i0data_sorted, x5.size()*x4.size(), i1data_sorted, x5.size()*x4.size(),
             1.0, odata_sorted, a1.size()*a2.size());
    }
  }
  sort_indices<2,3,4,5,0,1,1,1,1,1>(odata_sorted, odata, a1.size(), a2.size(), x0.size(), x1.size(), x3.size(), x2.size());
  out()->put_block(odata, x0, x1, x3, x2, a1, a2);
}

void Task767::Task_local::compute() {
  const Index x5 = b(0);
  const Index x0 = b(1);
  const Index x4 = b(2);
  const Index x1 = b(3);
  const Index x3 = b(4);
  const Index x2 = b(5);
  // tensor label: I1158
  std::unique_ptr<double[]> odata = out()->move_block(x5, x0, x4, x1, x3, x2);
  {
    // tensor label: Gamma360
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x0, x4, x1, x3, x2);
    sort_indices<0,1,2,3,4,5,1,1,1,2>(i0data, odata, x5.size(), x0.size(), x4.size(), x1.size(), x3.size(), x2.size());
  }
  out()->put_block(odata, x5, x0, x4, x1, x3, x2);
}

void Task768::Task_local::compute() {
  const Index c3 = b(0);
  const Index c2 = b(1);
  // tensor label: den2
  std::unique_ptr<double[]> odata = out()->move_block(c3, c2);
  {
    // tensor label: I875
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, c2);
    sort_indices<0,1,1,1,1,1>(i0data, odata, c3.size(), c2.size());
  }
  out()->put_block(odata, c3, c2);
}

void Task769::Task_local::compute() {
  const Index c3 = b(0);
  const Index c2 = b(1);
  // tensor label: I875
  std::unique_ptr<double[]> odata = out()->move_block(c3, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, c2), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& x0 : *range_[1]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0, c2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0, c2, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size(), c2.size(), x1.size());
        // tensor label: I876
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, c1, c3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, c1, c3)]);
        sort_indices<2,0,1,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), c1.size(), c3.size());
        dgemm_("T", "N", c2.size(), c3.size(), x0.size()*x1.size()*c1.size(),
               1.0, i0data_sorted, x0.size()*x1.size()*c1.size(), i1data_sorted, x0.size()*x1.size()*c1.size(),
               1.0, odata_sorted, c2.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c2.size(), c3.size());
  out()->put_block(odata, c3, c2);
}

void Task770::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index c1 = b(2);
  const Index c3 = b(3);
  // tensor label: I876
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, c1, c3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, c1, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, c1, c3), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x3, c3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x3, c3, x2)]);
      sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x3.size(), c3.size(), x2.size());
      // tensor label: I877
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x3, x1, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x3, x1, x2)]);
      sort_indices<3,1,0,2,0,1,1,1>(i1data, i1data_sorted, x0.size(), x3.size(), x1.size(), x2.size());
      dgemm_("T", "N", c1.size()*c3.size(), x0.size()*x1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c1.size()*c3.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, c1.size(), c3.size(), x0.size(), x1.size());
  out()->put_block(odata, x0, x1, c1, c3);
}

void Task771::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x1 = b(2);
  const Index x2 = b(3);
  // tensor label: I877
  std::unique_ptr<double[]> odata = out()->move_block(x0, x3, x1, x2);
  {
    // tensor label: Gamma94
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x3, x1, x2);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x0.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, x0, x3, x1, x2);
}

void Task772::Task_local::compute() {
  const Index c3 = b(0);
  const Index c2 = b(1);
  // tensor label: I875
  std::unique_ptr<double[]> odata = out()->move_block(c3, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, c2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& a1 : *range_[2]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, c2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, c2, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
        // tensor label: I969
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, a1, c3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, a1, c3)]);
        sort_indices<0,2,1,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), a1.size(), c3.size());
        dgemm_("T", "N", c2.size(), c3.size(), x0.size()*x1.size()*a1.size(),
               1.0, i0data_sorted, x0.size()*x1.size()*a1.size(), i1data_sorted, x0.size()*x1.size()*a1.size(),
               1.0, odata_sorted, c2.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c2.size(), c3.size());
  out()->put_block(odata, c3, c2);
}

void Task773::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index a1 = b(2);
  const Index c3 = b(3);
  // tensor label: I969
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, a1, c3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, a1, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, a1, c3), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a1, c3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a1, c3, x2)]);
      sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), a1.size(), c3.size(), x2.size());
      // tensor label: I970
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x0, x1, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x0, x1, x2)]);
      sort_indices<3,0,1,2,0,1,1,1>(i1data, i1data_sorted, x3.size(), x0.size(), x1.size(), x2.size());
      dgemm_("T", "N", a1.size()*c3.size(), x0.size()*x1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, a1.size()*c3.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, a1.size(), c3.size(), x0.size(), x1.size());
  out()->put_block(odata, x0, x1, a1, c3);
}

void Task774::Task_local::compute() {
  const Index x3 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index x2 = b(3);
  // tensor label: I970
  std::unique_ptr<double[]> odata = out()->move_block(x3, x0, x1, x2);
  {
    // tensor label: Gamma32
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x1, x2);
    sort_indices<0,1,2,3,1,1,-1,4>(i0data, odata, x3.size(), x0.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, x3, x0, x1, x2);
}

void Task775::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index a1 = b(2);
  const Index c3 = b(3);
  // tensor label: I969
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, a1, c3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, a1, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, a1, c3), 0.0);
  for (auto& x2 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a1, x3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a1, x3, x2)]);
      sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a1.size(), x3.size(), x2.size());
      // tensor label: I979
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, x1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, x1, x0)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
      dgemm_("T", "N", c3.size()*a1.size(), x1.size()*x0.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, c3.size()*a1.size());
    }
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, c3.size(), a1.size(), x1.size(), x0.size());
  out()->put_block(odata, x0, x1, a1, c3);
}

void Task776::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I979
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2, x1, x0);
  {
    // tensor label: Gamma35
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
    sort_indices<0,1,2,3,1,1,1,4>(i0data, odata, x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x3, x2, x1, x0);
}

void Task777::Task_local::compute() {
  const Index x2 = b(0);
  const Index c2 = b(1);
  // tensor label: den2
  std::unique_ptr<double[]> odata = out()->move_block(x2, c2);
  {
    // tensor label: I878
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, c2);
    sort_indices<0,1,1,1,1,1>(i0data, odata, x2.size(), c2.size());
  }
  out()->put_block(odata, x2, c2);
}

void Task778::Task_local::compute() {
  const Index x2 = b(0);
  const Index c2 = b(1);
  // tensor label: I878
  std::unique_ptr<double[]> odata = out()->move_block(x2, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, c2), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& x0 : *range_[1]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0, c2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0, c2, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size(), c2.size(), x1.size());
        // tensor label: I879
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, x2, c1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, x2, c1)]);
        sort_indices<3,0,1,2,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), x2.size(), c1.size());
        dgemm_("T", "N", c2.size(), x2.size(), x0.size()*x1.size()*c1.size(),
               1.0, i0data_sorted, x0.size()*x1.size()*c1.size(), i1data_sorted, x0.size()*x1.size()*c1.size(),
               1.0, odata_sorted, c2.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c2.size(), x2.size());
  out()->put_block(odata, x2, c2);
}

void Task779::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x2 = b(2);
  const Index c1 = b(3);
  // tensor label: I879
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, x2, c1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x2, c1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, c1, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, c1, x3)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c1.size(), x3.size());
        // tensor label: I880
        std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x4, x0, x3, x1, x2);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x4, x0, x3, x1, x2)]);
        sort_indices<3,1,0,2,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x4.size(), x0.size(), x3.size(), x1.size(), x2.size());
        dgemm_("T", "N", c1.size(), x0.size()*x1.size()*x2.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, c1.size(), x0.size(), x1.size(), x2.size());
  out()->put_block(odata, x0, x1, x2, c1);
}

void Task780::Task_local::compute() {
  const Index x5 = b(0);
  const Index x4 = b(1);
  const Index x0 = b(2);
  const Index x3 = b(3);
  const Index x1 = b(4);
  const Index x2 = b(5);
  // tensor label: I880
  std::unique_ptr<double[]> odata = out()->move_block(x5, x4, x0, x3, x1, x2);
  {
    // tensor label: Gamma2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, x0, x3, x1, x2);
    sort_indices<0,1,2,3,4,5,1,1,1,2>(i0data, odata, x5.size(), x4.size(), x0.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, x5, x4, x0, x3, x1, x2);
}

void Task781::Task_local::compute() {
  const Index x2 = b(0);
  const Index c2 = b(1);
  // tensor label: I878
  std::unique_ptr<double[]> odata = out()->move_block(x2, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, c2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& a1 : *range_[2]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, c2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, c2, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
        // tensor label: I984
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x1, x2, a1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x1, x2, a1)]);
        sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x0.size(), x1.size(), x2.size(), a1.size());
        dgemm_("T", "N", c2.size(), x2.size(), x0.size()*x1.size()*a1.size(),
               1.0, i0data_sorted, x0.size()*x1.size()*a1.size(), i1data_sorted, x0.size()*x1.size()*a1.size(),
               1.0, odata_sorted, c2.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c2.size(), x2.size());
  out()->put_block(odata, x2, c2);
}

void Task782::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x2 = b(2);
  const Index a1 = b(3);
  // tensor label: I984
  std::unique_ptr<double[]> odata = out()->move_block(x0, x1, x2, a1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x5 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, a1, x4, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, a1, x4, x3)]);
        sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, x5.size(), a1.size(), x4.size(), x3.size());
        // tensor label: I985
        std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x0, x4, x3, x1, x2);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x0, x4, x3, x1, x2)]);
        sort_indices<3,2,0,1,4,5,0,1,1,1>(i1data, i1data_sorted, x5.size(), x0.size(), x4.size(), x3.size(), x1.size(), x2.size());
        dgemm_("T", "N", a1.size(), x0.size()*x1.size()*x2.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, a1.size());
      }
    }
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a1.size(), x0.size(), x1.size(), x2.size());
  out()->put_block(odata, x0, x1, x2, a1);
}

void Task783::Task_local::compute() {
  const Index x5 = b(0);
  const Index x0 = b(1);
  const Index x4 = b(2);
  const Index x3 = b(3);
  const Index x1 = b(4);
  const Index x2 = b(5);
  // tensor label: I985
  std::unique_ptr<double[]> odata = out()->move_block(x5, x0, x4, x3, x1, x2);
  {
    // tensor label: Gamma37
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x0, x4, x3, x1, x2);
    sort_indices<0,1,2,3,4,5,1,1,1,4>(i0data, odata, x5.size(), x0.size(), x4.size(), x3.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, x5, x0, x4, x3, x1, x2);
}

void Task784::Task_local::compute() {
  const Index x2 = b(0);
  const Index a3 = b(1);
  // tensor label: den2
  std::unique_ptr<double[]> odata = out()->move_block(x2, a3);
  {
    // tensor label: I881
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, a3);
    sort_indices<0,1,1,1,1,1>(i0data, odata, x2.size(), a3.size());
  }
  out()->put_block(odata, x2, a3);
}

void Task785::Task_local::compute() {
  const Index x2 = b(0);
  const Index a3 = b(1);
  // tensor label: I881
  std::unique_ptr<double[]> odata = out()->move_block(x2, a3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, a3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, a3), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& x0 : *range_[1]) {
      for (auto& c2 : *range_[0]) {
        for (auto& x1 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0, c2, x1);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0, c2, x1)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size(), c2.size(), x1.size());
          // tensor label: I882
          std::unique_ptr<double[]> i1data = in(1)->get_block(x1, x0, x2, c1, a3, c2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, x0, x2, c1, a3, c2)]);
          sort_indices<3,1,5,0,2,4,0,1,1,1>(i1data, i1data_sorted, x1.size(), x0.size(), x2.size(), c1.size(), a3.size(), c2.size());
          dgemm_("T", "N", 1, x2.size()*a3.size(), x1.size()*x0.size()*c1.size()*c2.size(),
                 1.0, i0data_sorted, x1.size()*x0.size()*c1.size()*c2.size(), i1data_sorted, x1.size()*x0.size()*c1.size()*c2.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x2.size(), a3.size());
  out()->put_block(odata, x2, a3);
}

void Task786::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index x2 = b(2);
  const Index c1 = b(3);
  const Index a3 = b(4);
  const Index c2 = b(5);
  // tensor label: I882
  std::unique_ptr<double[]> odata = out()->move_block(x1, x0, x2, c1, a3, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, x0, x2, c1, a3, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, x2, c1, a3, c2), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a3, c2, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a3, c2, x3)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a3.size(), c2.size(), x3.size());
    // tensor label: I883
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, x3, x0, x2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, x3, x0, x2)]);
    sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, x1.size(), x3.size(), x0.size(), x2.size());
    dgemm_("T", "N", c1.size()*a3.size()*c2.size(), x1.size()*x0.size()*x2.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, c1.size()*a3.size()*c2.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, c1.size(), a3.size(), c2.size(), x1.size(), x0.size(), x2.size());
  out()->put_block(odata, x1, x0, x2, c1, a3, c2);
}

void Task787::Task_local::compute() {
  const Index x1 = b(0);
  const Index x3 = b(1);
  const Index x0 = b(2);
  const Index x2 = b(3);
  // tensor label: I883
  std::unique_ptr<double[]> odata = out()->move_block(x1, x3, x0, x2);
  {
    // tensor label: Gamma3
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x3, x0, x2);
    sort_indices<0,1,2,3,1,1,-1,2>(i0data, odata, x1.size(), x3.size(), x0.size(), x2.size());
  }
  out()->put_block(odata, x1, x3, x0, x2);
}

void Task788::Task_local::compute() {
  const Index x2 = b(0);
  const Index a3 = b(1);
  // tensor label: I881
  std::unique_ptr<double[]> odata = out()->move_block(x2, a3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, a3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, a3), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& a1 : *range_[2]) {
      for (auto& c2 : *range_[0]) {
        for (auto& x1 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, c2, x1);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, c2, x1)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
          // tensor label: I993
          std::unique_ptr<double[]> i1data = in(1)->get_block(x2, x1, x0, a3, c2, a1);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x2, x1, x0, a3, c2, a1)]);
          sort_indices<2,5,4,1,0,3,0,1,1,1>(i1data, i1data_sorted, x2.size(), x1.size(), x0.size(), a3.size(), c2.size(), a1.size());
          dgemm_("T", "N", 1, x2.size()*a3.size(), x1.size()*x0.size()*c2.size()*a1.size(),
                 1.0, i0data_sorted, x1.size()*x0.size()*c2.size()*a1.size(), i1data_sorted, x1.size()*x0.size()*c2.size()*a1.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x2.size(), a3.size());
  out()->put_block(odata, x2, a3);
}

void Task789::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a3 = b(3);
  const Index c2 = b(4);
  const Index a1 = b(5);
  // tensor label: I993
  std::unique_ptr<double[]> odata = out()->move_block(x2, x1, x0, a3, c2, a1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, x1, x0, a3, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, a3, c2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a3, c2, a1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a3, c2, a1)]);
    sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a3.size(), c2.size(), a1.size());
    // tensor label: I994
    std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, x1, x0)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
    dgemm_("T", "N", a3.size()*c2.size()*a1.size(), x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, a3.size()*c2.size()*a1.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, a3.size(), c2.size(), a1.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x2, x1, x0, a3, c2, a1);
}

void Task790::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I994
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2, x1, x0);
  {
    // tensor label: Gamma35
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
    sort_indices<0,1,2,3,1,1,-1,4>(i0data, odata, x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x3, x2, x1, x0);
}

void Task791::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a3 = b(3);
  const Index c2 = b(4);
  const Index a1 = b(5);
  // tensor label: I993
  std::unique_ptr<double[]> odata = out()->move_block(x2, x1, x0, a3, c2, a1);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, x1, x0, a3, c2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, a3, c2, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a1, c2, a3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a1, c2, a3)]);
    sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a1.size(), c2.size(), a3.size());
    // tensor label: I997
    std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x0, x1, x2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x0, x1, x2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), x0.size(), x1.size(), x2.size());
    dgemm_("T", "N", a1.size()*c2.size()*a3.size(), x0.size()*x1.size()*x2.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, a1.size()*c2.size()*a3.size());
  }
  sort_indices<5,4,3,2,1,0,1,1,1,1>(odata_sorted, odata, a1.size(), c2.size(), a3.size(), x0.size(), x1.size(), x2.size());
  out()->put_block(odata, x2, x1, x0, a3, c2, a1);
}

void Task792::Task_local::compute() {
  const Index x3 = b(0);
  const Index x0 = b(1);
  const Index x1 = b(2);
  const Index x2 = b(3);
  // tensor label: I997
  std::unique_ptr<double[]> odata = out()->move_block(x3, x0, x1, x2);
  {
    // tensor label: Gamma32
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x1, x2);
    sort_indices<0,1,2,3,1,1,1,4>(i0data, odata, x3.size(), x0.size(), x1.size(), x2.size());
  }
  out()->put_block(odata, x3, x0, x1, x2);
}

void Task793::Task_local::compute() {
  const Index x2 = b(0);
  const Index a3 = b(1);
  // tensor label: I881
  std::unique_ptr<double[]> odata = out()->move_block(x2, a3);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, a3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, a3), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& x0 : *range_[1]) {
        for (auto& x1 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, x0, x1);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, x0, x1)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), x0.size(), x1.size());
          // tensor label: I1035
          std::unique_ptr<double[]> i1data = in(1)->get_block(x2, x1, x0, a3, c1, a2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x2, x1, x0, a3, c1, a2)]);
          sort_indices<4,5,2,1,0,3,0,1,1,1>(i1data, i1data_sorted, x2.size(), x1.size(), x0.size(), a3.size(), c1.size(), a2.size());
          dgemm_("T", "N", 1, x2.size()*a3.size(), x1.size()*x0.size()*c1.size()*a2.size(),
                 1.0, i0data_sorted, x1.size()*x0.size()*c1.size()*a2.size(), i1data_sorted, x1.size()*x0.size()*c1.size()*a2.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x2.size(), a3.size());
  out()->put_block(odata, x2, a3);
}

void Task794::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a3 = b(3);
  const Index c1 = b(4);
  const Index a2 = b(5);
  // tensor label: I1035
  std::unique_ptr<double[]> odata = out()->move_block(x2, x1, x0, a3, c1, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, x1, x0, a3, c1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, a3, c1, a2), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a3, c1, a2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a3, c1, a2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a3.size(), c1.size(), a2.size());
    // tensor label: I1036
    std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, x1, x0)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
    dgemm_("T", "N", a3.size()*c1.size()*a2.size(), x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, a3.size()*c1.size()*a2.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, a3.size(), c1.size(), a2.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x2, x1, x0, a3, c1, a2);
}

void Task795::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1036
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2, x1, x0);
  {
    // tensor label: Gamma35
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
    sort_indices<0,1,2,3,1,1,1,2>(i0data, odata, x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x3, x2, x1, x0);
}

void Task796::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index a3 = b(3);
  const Index c1 = b(4);
  const Index a2 = b(5);
  // tensor label: I1035
  std::unique_ptr<double[]> odata = out()->move_block(x2, x1, x0, a3, c1, a2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, x1, x0, a3, c1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1, x0, a3, c1, a2), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a2, c1, a3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a2, c1, a3)]);
    sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a2.size(), c1.size(), a3.size());
    // tensor label: I1039
    std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, x1, x0)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
    dgemm_("T", "N", a2.size()*c1.size()*a3.size(), x2.size()*x1.size()*x0.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, a2.size()*c1.size()*a3.size());
  }
  sort_indices<3,4,5,2,1,0,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), a3.size(), x2.size(), x1.size(), x0.size());
  out()->put_block(odata, x2, x1, x0, a3, c1, a2);
}

void Task797::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I1039
  std::unique_ptr<double[]> odata = out()->move_block(x3, x2, x1, x0);
  {
    // tensor label: Gamma35
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
    sort_indices<0,1,2,3,1,1,-1,4>(i0data, odata, x3.size(), x2.size(), x1.size(), x0.size());
  }
  out()->put_block(odata, x3, x2, x1, x0);
}

void Task798::Task_local::compute() {
  const Index c2 = b(0);
  const Index x3 = b(1);
  // tensor label: den2
  std::unique_ptr<double[]> odata = out()->move_block(c2, x3);
  {
    // tensor label: I884
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, c2);
    sort_indices<1,0,1,1,1,1>(i0data, odata, x3.size(), c2.size());
  }
  out()->put_block(odata, c2, x3);
}

void Task799::Task_local::compute() {
  const Index x3 = b(0);
  const Index c2 = b(1);
  // tensor label: I884
  std::unique_ptr<double[]> odata = out()->move_block(x3, c2);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, c2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, c2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& x1 : *range_[1]) {
      for (auto& c1 : *range_[0]) {
        for (auto& x2 : *range_[1]) {
          // tensor label: t2
          std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1, c1, x2);
          std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1, c1, x2)]);
          sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size(), c1.size(), x2.size());
          // tensor label: I885
          std::unique_ptr<double[]> i1data = in(1)->get_block(x2, x3, x1, x0, c1, c2);
          std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x2, x3, x1, x0, c1, c2)]);
          sort_indices<3,2,4,0,1,5,0,1,1,1>(i1data, i1data_sorted, x2.size(), x3.size(), x1.size(), x0.size(), c1.size(), c2.size());
          dgemm_("T", "N", 1, x3.size()*c2.size(), x2.size()*x1.size()*x0.size()*c1.size(),
                 1.0, i0data_sorted, x2.size()*x1.size()*x0.size()*c1.size(), i1data_sorted, x2.size()*x1.size()*x0.size()*c1.size(),
                 1.0, odata_sorted, 1);
        }
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x3.size(), c2.size());
  out()->put_block(odata, x3, c2);
}


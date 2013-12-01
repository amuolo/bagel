//
// BAGEL - Parallel electron correlation program.
// Filename: inline.h
// Copyright (C) 2009 Toru Shiozaki
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


#ifndef __src_rysint_inline_h
#define __src_rysint_inline_h

// TODO Temporary hack to avoid having to set up complex inline_erf
// Figure out what's the best way to handle integral screening for London orbitals
#include <complex>
#include <stdexcept>
inline std::complex<double> inline_erf (std::complex<double> z) {
  throw std::runtime_error("Inline erf has not been implemented for complex arguments.");
}

inline double inline_erf(const double inpt) {
  static const double a[65] = {
    0.00000000005958930743, -0.00000000113739022964, 0.00000001466005199839, -0.00000016350354461960,
    0.00000164610044809620, -0.00001492559551950604, 0.00012055331122299265, -0.00085483269811296660,
    0.00522397762482322257, -0.02686617064507733420, 0.11283791670954881569, -0.37612638903183748117,
    1.12837916709551257377,
    0.00000000002372510631, -0.00000000045493253732, 0.00000000590362766598, -0.00000006642090827576,
    0.00000067595634268133, -0.00000621188515924000, 0.00005103883009709690, -0.00037015410692956173,
    0.00233307631218880978, -0.01254988477182192210, 0.05657061146827041994, -0.21379664776456006580,
    0.84270079294971486929,
    0.00000000000949905026, -0.00000000018310229805, 0.00000000239463074000, -0.00000002721444369609,
    0.00000028045522331686, -0.00000261830022482897, 0.00002195455056768781, -0.00016358986921372656,
    0.00107052153564110318, -0.00608284718113590151, 0.02986978465246258244, -0.13055593046562267625,
    0.67493323603965504676,
    0.00000000000382722073, -0.00000000007421598602, 0.00000000097930574080, -0.00000001126008898854,
    0.00000011775134830784, -0.00000111992758382650, 0.00000962023443095201, -0.00007404402135070773,
    0.00050689993654144881, -0.00307553051439272889, 0.01668977892553165586, -0.08548534594781312114,
    0.56909076642393639985,
    0.00000000000155296588, -0.00000000003032205868, 0.00000000040424830707, -0.00000000471135111493,
    0.00000005011915876293, -0.00000048722516178974, 0.00000430683284629395, -0.00003445026145385764,
    0.00024879276133931664, -0.00162940941748079288, 0.00988786373932350462, -0.05962426839442303805,
    0.49766113250947636708 };
  static const double b[65] = {
    -0.00000000029734388465,  0.00000000269776334046, -0.00000000640788827665, -0.00000001667820132100,
    -0.00000021854388148686,  0.00000266246030457984,  0.00001612722157047886, -0.00025616361025506629,
     0.00015380842432375365,  0.00815533022524927908, -0.01402283663896319337, -0.19746892495383021487,
     0.71511720328842845913,
    -0.00000000001951073787, -0.00000000032302692214,  0.00000000522461866919,  0.00000000342940918551,
    -0.00000035772874310272,  0.00000019999935792654,  0.00002687044575042908, -0.00011843240273775776,
    -0.00080991728956032271,  0.00661062970502241174,  0.00909530922354827295, -0.20160072778491013140,
     0.51169696718727644908,
     0.00000000003147682272, -0.00000000048465972408,  0.00000000063675740242,  0.00000003377623323271,
    -0.00000015451139637086, -0.00000203340624738438,  0.00001947204525295057,  0.00002854147231653228,
    -0.00101565063152200272,  0.00271187003520095655,  0.02328095035422810727, -0.16725021123116877197,
     0.32490054966649436974,
     0.00000000002319363370, -0.00000000006303206648, -0.00000000264888267434,  0.00000002050708040581,
     0.00000011371857327578, -0.00000211211337219663,  0.00000368797328322935,  0.00009823686253424796,
    -0.00065860243990455368, -0.00075285814895230877,  0.02585434424202960464, -0.11637092784486193258,
     0.18267336775296612024,
    -0.00000000000367789363,  0.00000000020876046746, -0.00000000193319027226, -0.00000000435953392472,
     0.00000018006992266137, -0.00000078441223763969, -0.00000675407647949153,  0.00008428418334440096,
    -0.00017604388937031815, -0.00239729611435071610,  0.02064129023876022970, -0.06905562880005864105,
     0.09084526782065478489 };

  double t = inpt;
  if (t < 2.2) {
    t *= t;
    int k = static_cast<int>(t);
    t = t - static_cast<double>(k);
    k *= 13;
    t = ((((((((((((a[k] * t + a[k + 1]) * t + a[k + 2]) * t + a[k + 3]) * t
      + a[k + 4]) * t + a[k + 5]) * t + a[k + 6]) * t + a[k + 7]) * t + a[k + 8]) * t
      + a[k + 9]) * t + a[k + 10]) * t + a[k + 11]) * t + a[k + 12]) * inpt;
  } else if (t < 6.9) {
    int k = static_cast<int>(t);
    t = t - static_cast<double>(k);
    k = 13 * (k - 2);
    t = (((((((((((b[k] * t + b[k + 1]) * t + b[k + 2]) * t + b[k + 3]) * t
      + b[k + 4]) * t + b[k + 5]) * t + b[k + 6]) * t + b[k + 7]) * t + b[k + 8]) * t
      + b[k + 9]) * t + b[k + 10]) * t + b[k + 11]) * t + b[k + 12];
    t *= t;
    t *= t;
    t *= t;
    t = 1.0 - t * t;
  } else {
    t = 1.0;
  }
  return t;
};

// crude fix to avoid type mismatches in compute_ssss - should improve upon this
#include <cassert>
template <typename DataType>
inline DataType londonfactor (std::complex<double> pow) {
  assert(0);
  return 1.0;
}

template <>
inline double londonfactor <double> (std::complex<double> pow) {
  return 1.0;
}

template <>
inline std::complex<double> londonfactor <std::complex<double>> (std::complex<double> pow) {
  return std::exp(pow);
}

#endif

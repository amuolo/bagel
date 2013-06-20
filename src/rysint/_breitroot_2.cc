//
// BAGEL - Parallel electron correlation program.
// Filename: _breitroot_2.cc
// Copyright (C) 2013 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
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

#include <algorithm>
#include <src/rysint/breitrootlist.h>

using namespace std;
using namespace bagel;

void BreitRootList::breitroot2(const double* ta, double* rr, double* ww, const int n) {

  constexpr double ax[2] = {9.188611699158103e-01,4.081138830084189e+00};
  constexpr double aw[2] = {3.616815117731377e-01,8.143195095324129e-02};
  constexpr double x[768] = {  5.115590067861033e-01, -3.307842995243011e-02,  1.090593163356171e-03, -2.614955387247384e-06, -1.857935327442760e-06,
  8.655863904704325e-08,  7.270258092075956e-10, -2.215785346351861e-10,  7.054575966183911e-12,  2.019714551696680e-13, -2.484631690486642e-14,  5.601207484665491e-16,
  1.581464307536534e+00, -3.170168030388232e-02, -1.286925682891906e-03, -1.314833535308483e-05,  1.980723941005067e-06,  1.254497201763767e-07,  9.328379319924865e-10,
 -2.682190090794000e-10, -1.450242705105992e-11,  8.186642101764643e-17,  3.670224988683985e-14,  1.708331143869597e-15,  3.959534126894955e-01, -2.485531660507064e-02,
  9.364665541575576e-04, -1.916459358662121e-05, -3.146654840377524e-07,  5.642376181423777e-08, -2.237722494623814e-09, -9.779965598847356e-12,  4.030295874876818e-12,
 -1.746297694545616e-13,  2.841499623820265e-15,  2.617101487778328e-16,  1.434069867576850e+00, -4.190699911686519e-02, -1.176821166978905e-03,  3.645765250442579e-05,
  3.880412023056224e-06,  1.814321511192841e-08, -1.046368388943509e-08, -3.608599406898158e-10,  1.981810271495454e-11,  1.648965774029247e-12, -9.043997893752848e-15,
 -5.158733038996888e-15,  3.100278999326845e-01, -1.830189240153031e-02,  7.043060191164335e-04, -1.798449661307265e-05,  3.090778095432746e-07,  9.261674028836205e-09,
 -1.436629569484418e-09,  4.875286746776401e-11,  4.835380774171620e-13, -4.250844362463473e-14,  7.135568509976026e-16, -1.514377401468037e-16,  1.251786193776554e+00,
 -4.858690543726664e-02, -4.040056825564334e-04,  8.624354540933669e-05,  1.470848512412887e-06, -2.415193983545037e-07, -5.861748782190965e-09,  7.195294356634050e-10,
  2.297815624495679e-11, -2.136965378777029e-12, -8.737365672733127e-14,  6.245653490523088e-15,  2.468472082093741e-01, -1.344235467466489e-02,  5.195125444422287e-04,
 -1.295321823314932e-05,  2.631067096903037e-07, -8.522584052857772e-09, -9.262470580791936e-11,  3.816580204411906e-11, -1.212042483963120e-12, -4.375248954179923e-14,
  1.639971050228304e-15,  1.330197285479359e-16,  1.057591784674832e+00, -4.765942804780572e-02,  6.080409362829200e-04,  7.081249367551643e-05, -3.043719809450449e-06,
 -1.367306542408824e-07,  1.190816123173115e-08,  1.846584512289686e-10, -4.059404100871034e-11,  1.905004400732140e-13,  1.236497752486224e-13, -2.885843464091549e-15,
  2.004902750091524e-01, -9.848745339448012e-03,  3.840906409822067e-04, -9.955862798304797e-06,  1.304977820882167e-07, -3.102693388579068e-09,  3.309959975899389e-10,
 -6.360443020983994e-12, -9.410005459274013e-13,  5.264151110230479e-14,  8.438763910409263e-16, -1.415111131103578e-16,  8.807479325794025e-01, -4.033182204327514e-02,
  1.124815600271747e-03,  1.522537151518445e-05, -3.138803137069099e-06,  9.536627965547364e-08,  4.477308434327421e-09, -4.476384024954666e-10,  5.477230928419340e-12,
  1.043110203298494e-12, -5.645553994116191e-14, -7.363548183901185e-16,  1.665309538210805e-01, -7.220788525902543e-03,  2.762350123065073e-04, -8.031942955863132e-06,
  1.232777003860304e-07,  1.019587413054849e-09,  2.344779034675793e-12, -9.555366730737254e-12,  4.401978788765852e-13,  8.256412431418129e-15, -1.525891562936721e-15,
  4.246076310216914e-17,  7.375856121276416e-01, -3.129197477988000e-02,  1.077928216988390e-03, -1.750925408218895e-05, -9.777118715138703e-07,  9.199635968853149e-08,
 -2.859941384272876e-09, -6.049563009340650e-11,  1.001579799732703e-11, -3.837796084131446e-13, -3.829374267549753e-15,  1.111794699819299e-15,  1.415061291537089e-01,
 -5.361674021342078e-03,  1.921904597279999e-04, -5.955431331117348e-06,  1.307547534621159e-07, -5.848364037916218e-10, -8.276290373313634e-11,  1.735580081085442e-12,
  1.534888450991906e-13, -1.181632414599215e-14,  2.425217111902483e-16,  1.373123128695907e-17,  6.281112670995618e-01, -2.366009890655921e-02,  8.222381969804096e-04,
 -2.224677364118438e-05,  1.733362836932658e-07,  2.708890890818743e-08, -1.985565495578395e-09,  6.817734174760363e-11, -1.952514293813998e-13, -1.214288937566819e-13,
  7.417990114077641e-15, -1.917115634273586e-16,  1.227301528070212e-01, -4.075928389037627e-03,  1.326019340652043e-04, -4.042591598254893e-06,  1.046251124917687e-07,
 -1.744864118223287e-09, -1.305430635120819e-11,  2.133274287415634e-12, -6.092947295197620e-14, -9.446536499274615e-16,  1.606848685607981e-16, -6.856467979962307e-18,
  5.450393033278371e-01, -1.807549412117877e-02,  5.830730944789909e-04, -1.712693906198743e-05,  3.785286169830006e-07, -7.702592550430474e-10, -5.094231601410907e-10,
  3.281600751091882e-11, -1.200136940070110e-12,  2.012329353018044e-14,  7.002852083227776e-16, -7.240283201690862e-17,  1.082774766087248e-01, -3.183377697935309e-03,
  9.297384486362947e-05, -2.648516997461897e-06,  7.028070273620281e-08, -1.561590712516481e-09,  2.018135804560467e-11,  3.904998478955378e-13, -3.634371918478861e-14,
  1.192659740003258e-15, -9.928418990534643e-18, -1.168406154399110e-18,  4.809047760801151e-01, -1.413426242671221e-02,  4.119147844311733e-04, -1.161415203611636e-05,
  2.960288287616774e-07, -5.560587007018340e-09, -6.185951813678313e-12,  7.291434342622302e-12, -4.310094652703817e-13,  1.608802478672160e-14, -3.810838206510300e-16,
  1.347279960158401e-18,  9.685434678197549e-02, -2.549791546180389e-03,  6.699867938370469e-05, -1.745742687894757e-06,  4.425202768280379e-08, -1.042062209063144e-09,
  2.040418042761631e-11, -2.146701083130070e-13, -6.018260489013268e-15,  4.665988268002562e-16, -1.627119936117200e-17,  3.032604896615008e-19,  4.301784620208108e-01,
 -1.132415657799607e-02,  2.974027450514185e-04, -7.728203754341176e-06,  1.937243283598703e-07, -4.380663024509932e-09,  7.270407955342073e-11,  1.414566279608121e-13,
 -8.405260901328491e-14,  4.661187790111499e-15, -1.727888087352884e-16,  4.631714571056237e-18,  8.760959166669724e-02, -2.086983445387690e-03,  4.969021609232911e-05,
 -1.180108479952441e-06,  2.776005208301650e-08, -6.345734223812763e-10,  1.347813741826900e-11, -2.382225277839331e-13,  2.200671186235974e-15,  6.702485780111784e-17,
 -4.810151969176921e-18,  1.712619984836280e-19,  3.891193116922538e-01, -9.269247900521336e-03,  2.206717390679281e-04, -5.237247944876194e-06,  1.228227943552651e-07,
 -2.776095962364913e-09,  5.672726793021298e-11, -8.609092390350999e-13, -9.433765151457107e-16,  8.075519173467148e-16, -4.273753759664623e-17,  1.550408537865773e-18,
  7.997653215307095e-02, -1.739417165954496e-03,  3.782618131421424e-05, -8.220105893531956e-07,  1.780980771310831e-08, -3.819736466999227e-10,  7.962099841655127e-12,
 -1.546069589565046e-13,  2.518022590249757e-15, -2.208250288317740e-17, -5.878601034065484e-19,  4.140854977998520e-20,  3.552171942706001e-01, -7.725633198329643e-03,
  1.680011624007968e-04, -3.650293031366065e-06,  7.902519926170547e-08, -1.689532908396296e-09,  3.483691343606958e-11, -6.529478217732428e-13,  9.307751384276189e-15,
 -6.253897464680603e-18, -6.606697617858679e-18,  3.393309909615599e-19,  7.356775988792458e-02, -1.471939779069788e-03,  2.944967513329593e-05, -5.891053491636518e-07,
  1.177416620061248e-08, -2.345539103945988e-10,  4.624905164891100e-12, -8.872451366707241e-14,  1.592527994166306e-15, -2.429320861320201e-17,  2.138853792774679e-19,
  4.164752871601986e-21,  3.267525546764185e-01, -6.537644514740350e-03,  1.308005647477579e-04, -2.616414200778701e-06,  5.228280667791218e-08, -1.040643735134465e-09,
  2.045554952379516e-11, -3.884872745555882e-13,  6.757884991590825e-15, -9.217496573639099e-17,  2.501518048243860e-19,  4.649761214940363e-20,  6.811051950584346e-02,
 -1.261738008056655e-03,  2.337338108862243e-05, -4.329672178548972e-07,  8.018402519735213e-09, -1.483529769605028e-10,  2.735470113437251e-12, -4.993822777248236e-14,
  8.885007966664436e-16, -1.487250493969090e-17,  2.150569087780794e-19, -1.955709788748985e-21,  3.025141272051972e-01, -5.604032142645232e-03,  1.038131929587791e-04,
 -1.923015017552010e-06,  3.561193849789583e-08, -6.587331681173796e-10,  1.213588401166751e-11, -2.208996817149344e-13,  3.894767015719058e-15, -6.345281548994500e-17,
  8.374688150656208e-19, -3.888630631626656e-21,  6.340744440033642e-02, -1.093556847785873e-03,  1.886001021438363e-05, -3.252655978104984e-07,  5.609303018740598e-09,
 -9.670784271147175e-11,  1.665572439595622e-12, -2.858940068307871e-14,  4.861226954620885e-16, -8.072899670665338e-18,  1.269043889086172e-19, -1.753910384818838e-21,
  2.816253333703463e-01, -4.857052830485861e-03,  8.376706626075101e-05, -1.444670551386734e-06,  2.491352137659850e-08, -4.295016835413523e-10,  7.395508191724011e-12,
 -1.268374271157734e-13,  2.150882961834294e-15, -3.543525519384053e-17,  5.444058194469866e-19, -6.995120121823061e-21,  5.931223342446505e-02, -9.568979033150735e-04,
  1.543784993116166e-05, -2.490617668231170e-07,  4.018104200246623e-09, -6.481930830907233e-11,  1.045342093826982e-12, -1.684050434916263e-14,  2.704266393226384e-16,
 -4.304793591283745e-18,  6.708218865215581e-20, -9.956389434777502e-22,  2.634363784527543e-01, -4.250079671647445e-03,  6.856749258080435e-05, -1.106212033621779e-06,
  1.784643769651815e-08, -2.878918402187952e-10,  4.642570882489484e-12, -7.477510281289000e-14,  1.199809327277290e-15, -1.905313384597218e-17,  2.948683822266951e-19,
 -4.293660653090707e-21,  5.571414203351570e-02, -8.443475438967812e-04,  1.279608214498265e-05, -1.939244591727090e-07,  2.938913116447371e-09, -4.453825387747239e-11,
  6.749081839186377e-13, -1.022402439479143e-14,  1.547217950887150e-16, -2.334363427376213e-18,  3.494177401754015e-20, -5.131308287574344e-22,  2.474553892129649e-01,
 -3.750185184395538e-03,  5.683403442198334e-05, -8.613190014690207e-07,  1.305322978592475e-08, -1.978168180591551e-10,  2.997565743524048e-12, -4.540675427558475e-14,
  6.869987886753789e-16, -1.035770734331366e-17,  1.547103795746370e-19, -2.258705600687865e-21,  5.252779685967107e-02, -7.505503022683158e-04,  1.072433614772099e-05,
 -1.532360645154822e-07,  2.189531750202016e-09, -3.128525208196825e-11,  4.470118886836525e-13, -6.386474435079384e-15,  9.121557610499553e-17, -1.301521005061957e-18,
  1.851952557197569e-20, -2.616099479528574e-22,  2.333031783701154e-01, -3.333583007505284e-03,  4.763233670032570e-05, -6.806007972436497e-07,  9.724844587469107e-09,
 -1.389539245768333e-10,  1.985403742445714e-12, -2.836511945094639e-14,  4.051048595573437e-16, -5.779124510221503e-18,  8.217971665549117e-20, -1.158763884629456e-21,
  4.968632160166619e-02, -6.715594375790502e-04,  9.076785377031802e-06, -1.226816667925785e-07,  1.658162928509585e-09, -2.241167466091173e-11,  3.029138957425827e-13,
 -4.094060036768232e-15,  5.532877478165340e-17, -7.475114271209733e-19,  1.008995091664268e-20, -1.358310624309859e-22,  2.206827136150618e-01, -2.982743625601526e-03,
  4.031470962044802e-05, -5.448928839828014e-07,  7.364761065762200e-09, -9.954185136029784e-11,  1.345396478540347e-12, -1.818376384765701e-14,  2.457390961358795e-16,
 -3.319840927807378e-18,  4.480318763408621e-20, -6.028055926652419e-22,  4.713658344523081e-02, -6.044145336224826e-04,  7.750178346105564e-06, -9.937759736277252e-08,
  1.274281196380885e-09, -1.633962035010055e-11,  2.095164466767680e-13, -2.686530475101766e-15,  3.444729109714684e-17, -4.416524715920268e-19,  5.660873489521843e-21,
 -7.248616345728866e-23,  2.093580045758699e-01, -2.684518296550614e-03,  3.442256003711856e-05, -4.413874310222390e-07,  5.659743408149126e-09, -7.257272286586233e-11,
  9.305709857180899e-13, -1.193226274736307e-14,  1.529975742417044e-16, -1.961570573513244e-18,  2.514112524882338e-20, -3.218737810080977e-22,  4.483583413751571e-02,
 -5.468598067256097e-04,  6.670014151531782e-06, -8.135373673662821e-08,  9.922663260424984e-10, -1.210260836877736e-11,  1.476146921811353e-13, -1.800443830515554e-15,
  2.195972395972643e-17, -2.678327820062299e-19,  3.266362218470657e-21, -3.981870502780891e-23,  1.991391840995886e-01, -2.428887915727213e-03,  2.962499084965162e-05,
 -3.613341218585026e-07,  4.407169181152786e-09, -5.375395791393385e-11,  6.556333512471233e-13, -7.996702700423626e-15,  9.753441358684224e-17, -1.189578685023885e-18,
  1.450734465048982e-20, -1.768441939940390e-22,  4.274929050774563e-02, -4.971520014741056e-04,  5.781619054522273e-06, -6.723722078507370e-08,  7.819338856853819e-10,
 -9.093484059925585e-12,  1.057524794315201e-13, -1.229845798513773e-15,  1.430243852775012e-17, -1.663285267141821e-19,  1.934252468306487e-21, -2.248883306601307e-23,
  1.898717620918677e-01, -2.208109782085836e-03,  2.567916764433774e-05, -2.986353559745092e-07,  3.472973771710365e-09, -4.038887708846607e-11,  4.697015836248626e-13,
 -5.462382529863951e-15,  6.352452880994042e-17, -7.387503905518868e-19,  8.590978622557884e-21, -9.988286832724887e-23,  4.084836147915499e-02, -4.539267303590240e-04,
  5.044253161517036e-06, -5.605417847209584e-08,  6.229011159328916e-10, -6.921978164709186e-12,  7.692036477696617e-14, -8.547761812213973e-16,  9.498681476870744e-18,
 -1.055537154502210e-19,  1.172953907460629e-21, -1.303241833285874e-23,  1.814287507580379e-01, -2.016123943349451e-03,  2.240414343346846e-05, -2.489656673285294e-07,
  2.766626792707786e-09, -3.074409365348543e-11,  3.416432180097605e-13, -3.796504132336804e-15,  4.218856662364304e-17, -4.688186509114654e-19,  5.209690557036524e-21,
 -5.788347318552912e-23,  3.910932858757287e-02, -4.161037843049597e-04,  4.427137094035002e-06, -4.710253448433166e-08,  5.011475153377876e-10, -5.331960047862873e-12,
  5.672940002510043e-14, -6.035725592127450e-16,  6.421710817129202e-18, -6.832377050458723e-20,  7.269293013235494e-22, -7.733225680629498e-24,  1.737048041021142e-01,
 -1.848132630990968e-03,  1.966321104006086e-05, -2.092067754880910e-07,  2.225855930578335e-09, -2.368199887348372e-11,  2.519646762249304e-13, -2.680778646007060e-15,
  2.852214667126482e-17, -3.034612685097576e-19,  3.228669031611344e-21, -3.434722694860775e-23,  3.751235017917547e-02, -3.828189479774918e-04,  3.906722618833418e-06,
 -3.986866820758455e-08,  4.068655135556685e-10, -4.152121290963219e-12,  4.237299704693096e-14, -4.324225488955825e-16,  4.412934415760798e-18, -4.503462711044607e-20,
  4.595846135511409e-22, -4.689628617929409e-24,  1.666117950527560e-01, -1.700297416666403e-03,  1.735178055195218e-05, -1.770774250266906e-07,  1.807100681101661e-09,
 -1.844172327924428e-11,  1.882004477346532e-13, -1.920612724009827e-15,  1.960012953281508e-17, -2.000221241011595e-19,  2.041253408690472e-21, -2.082906645383807e-23,
  3.604070027448779e-02, -3.533741672565131e-04,  3.464785676559873e-06, -3.397175259780199e-08,  3.330884165135611e-10, -3.265886647863835e-12,  3.202157465279004e-14,
 -3.139671865481616e-16,  3.078405570161244e-18, -3.018334730987194e-20,  2.959435755364595e-22, -2.901405982162662e-24,  1.600754348636962e-01, -1.569517880129114e-03,
  1.538890947347747e-05, -1.508861656060670e-07,  1.479418344132543e-09, -1.450549576978163e-11,  1.422244143000379e-13, -1.394491048522964e-15,  1.367279509875380e-17,
 -1.340598932733851e-19,  1.314438829355265e-21, -1.288664736060429e-23,  3.468018000876357e-02, -3.272006328486749e-04,  3.087073195973014e-06, -2.912592446513468e-08,
  2.747973313541951e-10, -2.592658420492131e-12,  2.446121893562556e-14, -2.307867580957224e-16,  2.177427371826173e-18, -2.054359606055953e-20,  1.938247542282010e-22,
 -1.828535164172717e-24,  1.540326590153357e-01, -1.453267644413789e-03,  1.371129252589041e-05, -1.293633305972120e-07,  1.220517414503261e-09, -1.151534018352493e-11,
  1.086449549699490e-13, -1.025043641798342e-15,  9.671083822915846e-18, -9.124476067275007e-20,  8.608762173388145e-22, -8.121472531498714e-24,  3.341865765313397e-02,
 -3.038310907479044e-04,  2.762329135515240e-06, -2.511415877201159e-08,  2.283294060496250e-10, -2.075893448800056e-12,  1.887331853266884e-14, -1.715898051650930e-16,
  1.560036258554401e-18, -1.418332005660627e-20,  1.289499293182889e-22, -1.172272045505999e-24,  1.484295842101930e-01, -1.349471392236237e-03,  1.226893579305027e-05,
 -1.115449992937963e-07,  1.014129267389283e-09, -9.220119032553209e-12,  8.382619228892415e-14, -7.621192837734931e-16,  6.928929809460241e-18, -6.299547756524196e-20,
  5.727334885236588e-22, -5.206667889682188e-24,  3.224570559064014e-02, -2.828788348674825e-04,  2.481584252856656e-06, -2.176995817630196e-08,  1.909792417695951e-10,
 -1.675385432140551e-12,  1.469749445132076e-14, -1.289353118399000e-16,  1.131098548364934e-18, -9.922680664598344e-21,  8.704775635915030e-23, -7.635768041359823e-25,
  1.432198959952590e-01, -1.256411561381392e-03,  1.102200221975502e-05, -9.669167068051765e-08,  8.482378239983122e-10, -7.441255291147624e-12,  6.527919262898337e-14,
 -5.726685651181740e-16,  5.023795060124980e-18, -4.407176914597448e-20,  3.866242149823921e-22, -3.391440453507684e-24,  3.115231121071156e-02, -2.640216003611512e-04,
  2.237631904283715e-06, -1.896434432720417e-08,  1.607263263775667e-10, -1.362185348732063e-12,  1.154477282048385e-14, -9.784408531515423e-17,  8.292467231647801e-19,
 -7.028019380277073e-21,  5.956376402832121e-23, -5.047776603346552e-25,  1.383635646944910e-01, -1.172656806592001e-03,  9.938483365059616e-06, -8.423048503391552e-08,
  7.138689424174626e-10, -6.050171345244190e-12,  5.127632136908501e-14, -4.345763091831214e-16,  3.683114612335851e-18, -3.121507767479609e-20,  2.645535562860263e-22,
 -2.241979286170885e-24,  3.013064473647286e-02, -2.469890932235562e-04,  2.024636801002478e-06, -1.659649874605311e-08,  1.360460160021587e-10, -1.115206210253301e-12,
  9.141648744552366e-15, -7.493658213199058e-17,  6.142755534071451e-19, -5.035383850899237e-21,  4.127641132567888e-23, -3.383312402341885e-25,  1.338258142095154e-01,
 -1.097006612059029e-03,  8.992461686182386e-06, -7.371365522189479e-08,  6.042508887773945e-10, -4.953208947367735e-12,  4.060280147195825e-14, -3.328322113782150e-16,
  2.728316197767537e-18, -2.236475022678784e-20,  1.833299420434717e-22, -1.502704442313957e-24,  2.917387131871288e-02, -2.315532472910093e-04,  1.837839954295680e-06,
 -1.458695024631033e-08,  1.157767394222730e-10, -9.189208960689651e-13,  7.293482416639348e-15, -5.788842759957454e-17,  4.594609074952642e-19, -3.646744855051840e-21,
  2.894424262857003e-23, -2.297162113166462e-25,  1.295762874315252e-01, -1.028448017710891e-03,  8.162800046979323e-06, -6.478820850398733e-08,  5.142245230800969e-10,
 -4.081404104894783e-12,  3.239413664613812e-14, -2.571125186526123e-16,  2.040704093150861e-18, -1.619708452009371e-20,  1.285563873697060e-22, -1.020288788548092e-24
  };
  constexpr double w[768] = {  1.945043469069972e-01, -3.639789063247634e-02,  4.617254554322831e-03, -4.674613687886327e-04,  4.001970673928960e-05,
 -2.988425295773276e-06,  1.984401020181226e-07, -1.185837473569078e-08,  6.426832379165732e-10, -3.175258101924518e-11,  1.434952667389169e-12, -5.940276724692428e-14,
  2.190610115688224e-01, -7.024607982676291e-02,  1.290421325400950e-02, -1.686573739294910e-03,  1.723482757502595e-04, -1.450526963070022e-05,  1.039379163111662e-06,
 -6.490685478452444e-08,  3.594525021344069e-09, -1.789527150405464e-10,  8.097924503953570e-12, -3.356637872399126e-13,  9.823321403533526e-02, -1.430188915304775e-02,
  1.484424731187746e-03, -1.280589198380916e-04,  9.628216909290967e-06, -6.449911097272039e-07,  3.915717175837509e-08, -2.177951357303633e-09,  1.116141308016238e-10,
 -5.294931915340748e-12,  2.332243230627690e-13, -9.523546698243739e-15,  6.171293650099800e-02, -1.666009122907664e-02,  2.771348042083407e-03, -3.374320040431647e-04,
  3.270668201351071e-05, -2.644708688036383e-06,  1.836421409876429e-07, -1.117857427310748e-08,  6.060250460070836e-10, -2.961917281896646e-11,  1.318073686224195e-12,
 -5.379949276658872e-14,  5.776877173366980e-02, -6.682806000011318e-03,  5.686627473232871e-04, -4.137186071828721e-05,  2.707281770787683e-06, -1.609865639355372e-07,
  8.776258246618596e-09, -4.458364227016332e-10,  2.123080371436932e-11, -9.437029413343499e-13,  3.942614333160809e-14, -1.563469856500737e-15,  2.249387375537949e-02,
 -4.657151374263271e-03,  6.745966260286204e-04, -7.458577122192590e-05,  6.708392083147733e-06, -5.127786539983816e-07,  3.413446852596869e-08, -2.008454331027449e-09,
  1.058721981131027e-10, -5.060807694742392e-12,  2.210542930679849e-13, -8.861113644142546e-15,  3.778218845260532e-02, -3.569911934680229e-03,  2.539442968748745e-04,
 -1.554876211745711e-05,  8.772929901021440e-07, -4.650233531922186e-08,  2.276419297960299e-09, -1.029929986234324e-10,  4.472758376244608e-12, -1.889378573114960e-13,
  7.370339007177473e-15, -2.603072746647932e-16,  1.081350950831668e-02, -1.579000045418042e-03,  1.899308415094991e-04, -1.869612603136470e-05,  1.527602715775300e-06,
 -1.076712065255091e-07,  6.755827169146576e-09, -3.815050399008765e-10,  1.939415982913958e-11, -8.947500104437416e-13,  3.816447315763238e-14, -1.515201976688135e-15,
  2.664713048276710e-02, -2.101386845777467e-03,  1.283824897578467e-04, -6.737641860288689e-06,  3.228753056747524e-07, -1.499184518640576e-08,  6.793303483830100e-10,
 -2.839617065495568e-11,  1.055799729808786e-12, -3.794481195212016e-14,  1.527784323510072e-15, -6.173180230377877e-17,  6.541284932270026e-03, -6.618574707771953e-04,
  6.215135830467721e-05, -5.341099598976291e-06,  3.964752712883382e-07, -2.535236526467383e-08,  1.445762148101529e-09, -7.641789718325539e-11,  3.776160953511003e-12,
 -1.701815158102459e-13,  6.854696879391421e-15, -2.540885856990337e-16,  1.988347415608124e-02, -1.328053052421625e-03,  7.089980551469199e-05, -3.299028286951001e-06,
  1.372356936005757e-07, -5.358132664607483e-09,  2.118266857733616e-10, -8.658031667537809e-12,  3.321067167152563e-13, -1.039443026201149e-14,  2.502334714140560e-16,
 -7.140778228756167e-18,  4.595766234991533e-03, -3.422841021045950e-04,  2.397029343570049e-05, -1.707861949988412e-06,  1.151289912357771e-07, -6.871211061830380e-09,
  3.572860635412653e-10, -1.667568281572686e-11,  7.420028378390595e-13, -3.283309773208957e-14,  1.397472468702219e-15, -5.221817867400867e-17,  1.549874370936701e-02,
 -8.885646451749243e-04,  4.166281423543384e-05, -1.748993522962198e-06,  6.623061002637410e-08, -2.269773503452196e-09,  7.332626796261888e-11, -2.473944065674597e-12,
  9.396435666313897e-14, -3.634429895355824e-15,  1.157938686197460e-16, -2.223874752531984e-18,  3.513836121566335e-03, -2.092325312569978e-04,  1.116065039398985e-05,
 -6.207114435984217e-07,  3.597292810278387e-08, -2.013072930330760e-09,  1.014600041772978e-10, -4.460242945791116e-12,  1.724410254411050e-13, -6.234437641203414e-15,
  2.353273184936375e-16, -9.725231730601329e-18,  1.249971479348344e-02, -6.241245529041944e-04,  2.579225697842625e-05, -9.755609406929680e-07,  3.416675130862103e-08,
 -1.095042509785297e-09,  3.176326781048492e-11, -8.535315664887272e-13,  2.383934137356713e-14, -8.187062982329493e-16,  3.294463272642168e-17, -1.215606491467206e-18,
  2.818952750870584e-03, -1.423300310219287e-04,  6.171679452352342e-06, -2.683244860705701e-07,  1.247290339166613e-08, -6.113789231927764e-10,  2.946477408095631e-11,
 -1.302874046605675e-12,  5.058043013413136e-14, -1.689817890479799e-15,  4.932222467354203e-17, -1.396741239875732e-18,  1.035297175822766e-02, -4.567504616743483e-04,
  1.675789088955770e-05, -5.695320825374891e-07,  1.830933786518049e-08, -5.535797438264206e-10,  1.544159226647898e-11, -3.883968695693752e-13,  8.772722426259246e-15,
 -1.941683585106975e-16,  5.503677687358362e-18, -2.221490918920434e-19,  2.331803983715025e-03, -1.031735729334560e-04,  3.842825552741903e-06, -1.378752726590508e-07,
  5.110356498447755e-09, -2.040932986102549e-10,  8.665578875779927e-12, -3.680278812911866e-13,  1.464267457380827e-14, -5.199360047885464e-16,  1.589666848939463e-17,
 -4.054713291794748e-19,  8.756878014963576e-03, -3.457716439521117e-04,  1.137217980538909e-05, -3.482171774306572e-07,  1.020372927659961e-08, -2.870576866556750e-10,
  7.668176029500514e-12, -1.902144229394929e-13,  4.246439929630575e-15, -8.252649730590296e-17,  1.412704956021055e-18, -2.797233657280692e-20,  1.971744861665263e-03,
 -7.790995176066116e-05,  2.573130364488072e-06, -8.020008588552776e-08,  2.487332526670908e-09, -8.048328296575102e-11,  2.810454662561703e-12, -1.049652061198592e-13,
  3.983169030624888e-15, -1.446005332436343e-16,  4.786164834353685e-18, -1.388838099302355e-19,  7.532696856664639e-03, -2.691125583809014e-04,  8.011711412873642e-06,
 -2.224537410311286e-07,  5.940503132960057e-09, -1.539813863569168e-10,  3.864813592825617e-12, -9.276898730609367e-14,  2.081237499403259e-15, -4.210938616402017e-17,
  7.273830329412413e-19, -9.868283270294100e-21,  1.695998766900988e-03, -6.060057155865366e-05,  1.806046954097548e-06, -5.040606073935009e-08,  1.372134760681804e-09,
 -3.763623314535549e-11,  1.079645569608016e-12, -3.337794542431092e-14,  1.108168794813433e-15, -3.789317203541292e-17,  1.263851583391203e-18, -3.924442954217676e-20,
  6.569536583087330e-03, -2.142860302578255e-04,  5.825129441210733e-06, -1.477668840543601e-07,  3.611648425858602e-09, -8.609003489242276e-11,  2.007276834228437e-12,
 -4.558186275254733e-14,  9.958054597934827e-16, -2.047137963785714e-17,  3.818254218616314e-19, -6.053889294343656e-21,  1.479123739689326e-03, -4.824785845288063e-05,
  1.311895597577526e-06, -3.332479114851625e-08,  8.192282223494293e-10, -1.991336430582552e-11,  4.902393159976667e-13, -1.261009838373504e-14,  3.484863996260125e-16,
 -1.036570940146474e-17,  3.211651615828985e-19, -9.866879184246346e-21,  5.795597674377297e-03, -1.739112066601964e-04,  4.349257546477774e-06, -1.015143633519246e-07,
  2.284279797979628e-09, -5.021747987676605e-11,  1.084592899431478e-12, -2.302420551808024e-14,  4.781035840885255e-16, -9.601072857927286e-18,  1.826877379177689e-19,
 -3.180829665944075e-21,  1.304869227964123e-03, -3.915608557530997e-05,  9.792903754911061e-07, -2.286506941216403e-08,  5.153341881255653e-10, -1.139791624197872e-11,
  2.509197135335047e-13, -5.604335004106729e-15,  1.304384882790791e-16, -3.247956801117783e-18,  8.709599237956105e-20, -2.452979085493423e-21,  5.162612787712353e-03,
 -1.434366282454930e-04,  3.321281779307569e-06, -7.177810528117229e-08,  1.495756956640102e-09, -3.046960090927542e-11,  6.107948931087732e-13, -1.208218302823316e-14,
  2.356978902905121e-16, -4.513303885600970e-18,  8.396667675482264e-20, -1.489864086295582e-21,  1.162353224260422e-03, -3.229454864682720e-05,  7.477909218796806e-07,
 -1.616224004491170e-08,  3.369385103171320e-10, -6.875556620800505e-12,  1.386644588808678e-13, -2.792965371349626e-15,  5.707687809085708e-17, -1.211222658692170e-18,
  2.736229846382009e-20, -6.645622607443781e-22,  4.637070845945917e-03, -1.199465311345758e-04,  2.585726094959363e-06, -5.202606037168789e-08,  1.009396152054924e-09,
 -1.914763810932315e-11,  3.576302217637934e-13, -6.601289325488273e-15,  1.205885395356113e-16, -2.177818373779897e-18,  3.871803323421619e-20, -6.713617136791405e-22,
  1.044028294906828e-03, -2.700575611853577e-05,  5.821732827820500e-07, -1.171382185739289e-08,  2.272916873631014e-10, -4.313585883052818e-12,  8.071011187962209e-14,
 -1.498492824981401e-15,  2.783389002434910e-17, -5.241043974684846e-19,  1.020811351342946e-20, -2.104036270249705e-22,  4.195055065287737e-03, -1.015097751582555e-04,
  2.047033929853922e-06, -3.852882660793245e-08,  6.992838358920734e-10, -1.240952821960450e-11,  2.168690767055325e-13, -3.747494101537074e-15,  6.417295175918273e-17,
 -1.089766453565390e-18,  1.833113844567983e-20, -3.042004127624891e-22,  9.445092109929459e-04, -2.285474701119772e-05,  4.608863181236458e-07, -8.674736243773025e-09,
  1.574469939441859e-10, -2.794391927696492e-12,  4.885870428389083e-14, -8.457532827004343e-16,  1.456213693384157e-17, -2.510453429155007e-19,  4.381720271192618e-21,
 -7.876511652802990e-23,  3.819086089925712e-03, -8.680986900096208e-05,  1.644456673548973e-06, -2.907493301837273e-08,  4.957045118170496e-10, -8.263548408305645e-12,
  1.356664573714354e-13, -2.202676904642147e-15,  3.545694566349948e-17, -5.666786307499723e-19,  8.994942272035355e-21, -1.416117395652271e-22,  8.598604606309698e-04,
 -1.954508823295673e-05,  3.702465442197013e-07, -6.546175780115640e-09,  1.116077001898004e-10, -1.860588342042340e-12,  3.055003692159113e-14, -4.962540120807069e-16,
  8.001613770127251e-18, -1.285231928222561e-19,  2.067570029170609e-21, -3.361561580289414e-23,  3.496123347313557e-03, -7.492648750665700e-05,  1.338211998637847e-06,
 -2.230780152470688e-08,  3.585886119980698e-10, -5.636078657445813e-12,  8.724200346813360e-14, -1.335573291466300e-15,  2.027440179596828e-17, -3.056999072149316e-19,
  4.582634333296571e-21, -6.829182725205641e-23,  7.871459715285290e-04, -1.686956581182868e-05,  3.012960645230615e-07, -5.022562912252431e-09,  8.073570085740638e-11,
 -1.268963349045982e-12,  1.964316955770358e-14, -3.007537644089128e-16,  4.567721532646482e-18, -6.897928362851929e-20,  1.038687910700184e-21, -1.566126288414147e-23,
  3.216260659640620e-03, -6.520191579859779e-05,  1.101559758444861e-06, -1.736990729903900e-08,  2.641159556026799e-10, -3.926746177905374e-12,  5.749638156102765e-14,
 -8.326214077546670e-16,  1.195674019554220e-17, -1.705707681344136e-19,  2.420072759569015e-21, -3.416473561113709e-23,  7.241353836647891e-04, -1.468009571425018e-05,
  2.480142270212204e-07, -3.910803971904072e-09,  5.946525616879249e-11, -8.841015307978121e-13,  1.294533148829056e-14, -1.874713839158491e-16,  2.692509944391105e-18,
 -3.842784950558762e-20,  5.459854667805578e-22, -7.738337628030461e-24,  2.971851960058780e-03, -5.715687171397996e-05,  9.161072828510593e-07, -1.370457145082350e-08,
  1.976933668169857e-10, -2.788430143992841e-12,  3.873443758791806e-14, -5.321519385329743e-16,  7.249997897205462e-18, -9.812621589034466e-20,  1.321043652374084e-21,
 -1.770194865268227e-23,  6.691071983910039e-04, -1.286876830244563e-05,  2.062599302143552e-07, -3.085559980494430e-09,  4.451031357531434e-11, -6.278103473814356e-13,
  8.721009004634993e-15, -1.198143339179309e-16,  1.632397887445214e-18, -2.209674327375226e-20,  2.976064831129896e-22, -3.992930023676793e-24,  2.756911353365460e-03,
 -5.043599391177738e-05,  7.689414475677458e-07, -1.094174962709010e-08,  1.501369614722626e-10, -2.014324509445344e-12,  2.661589703794807e-14, -3.478196038328152e-16,
  4.507465105956167e-18, -5.803112159448955e-20,  7.431749148151777e-22, -9.474284273426119e-24,  6.207137019781896e-04, -1.135557458384323e-05,  1.731258032662931e-07,
 -2.463515527382060e-09,  3.380307101729092e-11, -4.535216285722857e-13,  5.992524945605525e-15, -7.831116262994721e-17,  1.014859196365105e-18, -1.306619574414069e-20,
  1.673520402988302e-22, -2.134278267457397e-24,  2.566692749118712e-03, -4.477168067171011e-05,  6.508281799690706e-07, -8.830183896120627e-09,  1.155261628201407e-10,
 -1.477855066673588e-12,  1.861886383732765e-14, -2.319935209131887e-16,  2.866581492105684e-18, -3.518880163124252e-20,  4.296858440427339e-22, -5.223286781274362e-24,
  5.778863205741849e-04, -1.008026450311067e-05,  1.465328105150185e-07, -1.988100244880090e-09,  2.601051074037591e-11, -3.327364530713532e-13,  4.192004619898366e-15,
 -5.223295973941311e-17,  6.454074935467367e-19, -7.922787547261871e-21,  9.674727163006948e-23, -1.176194415315185e-24,  2.397389769935625e-03, -3.995957979964969e-05,
  5.550541303761516e-07, -7.195979101389933e-09,  8.996042979017076e-11, -1.099648744670608e-12,  1.323811796716491e-14, -1.576158398949223e-16,  1.860969763800434e-18,
 -2.182885253809950e-20,  2.547007736819785e-22, -2.958596873431716e-24,  5.397680550607052e-04, -8.996828525752888e-06,  1.249694530963936e-07, -1.620161933078478e-09,
  2.025443123647651e-11, -2.475839655564217e-13,  2.980538850816493e-15, -3.548693137602289e-17,  4.189943094106212e-19, -4.914741401329965e-21,  5.734608286631191e-23,
 -6.661507141725502e-25,  2.245917896263994e-03, -3.584165081753480e-05,  4.766649046076594e-07, -5.916681609165880e-09,  7.081906417301660e-11, -8.288251956860654e-13,
  9.553125390048775e-15, -1.089003677908955e-16,  1.231059571050120e-18, -1.382550544801754e-20,  1.544511354419223e-22, -1.717763850032902e-24,  5.056644313306589e-04,
 -8.069684118350838e-06,  1.073202579332179e-07, -1.332130371402445e-09,  1.594478670616692e-11, -1.866085230615476e-13,  2.150869249793067e-15, -2.451872536551322e-17,
  2.771709196949828e-19, -3.112790154329329e-21,  3.477449915236622e-23, -3.867557504713161e-25,  2.109753893259977e-03, -3.229425323373046e-05,  4.119540312476773e-07,
 -4.904693480184265e-09,  5.630952307456647e-11, -6.321098456313381e-13,  6.988323563608429e-15, -7.641080473939031e-17,  8.285188439799546e-19, -8.924877233417790e-21,
  9.563356468982618e-23, -1.020199957932079e-24,  4.750073475337538e-04, -7.270993843473603e-06,  9.275071955736716e-08, -1.104283038858212e-09,  1.267798925856739e-11,
 -1.423184107507723e-13,  1.573408658457356e-15, -1.720375727966458e-17,  1.865395544829196e-19, -2.009420601566528e-21,  2.153174261988803e-23, -2.296968594428240e-25,
  1.986815814651139e-03, -2.921963508743944e-05,  3.581138842308899e-07, -4.096443002128120e-09,  4.518553725971448e-11, -4.873406845972158e-13,  5.176492712791085e-15,
 -5.438008077489556e-17,  5.665130635259353e-19, -5.863166830747254e-21,  6.036188982102949e-23, -6.186772120739169e-25,  4.473280571589668e-04, -6.578749020504121e-06,
  8.062870593909914e-08, -9.223068771106407e-10,  1.017344357996334e-11, -1.097238908677442e-13,  1.165478154283543e-15, -1.224357876173217e-17,  1.275494124849939e-19,
 -1.320081662003026e-21,  1.359037472220700e-23, -1.392941749662784e-25,  1.875372193674711e-03, -2.653976214289440e-05,  3.129932694819358e-07, -3.445181956278101e-09,
  3.656756386801587e-11, -3.795076539087748e-13,  3.878955050388359e-15, -3.921121002908462e-17,  3.930715147602038e-19, -3.914579680341011e-21,  3.877992442402696e-23,
 -3.824748287398848e-25,  4.222367235353216e-04, -5.975380379648644e-06,  7.046987954732580e-08, -7.756766076133180e-10,  8.233122154303499e-12, -8.544547524181119e-14,
  8.733398505128578e-16, -8.828334401386690e-18,  8.849935459320739e-20, -8.813606799125386e-22,  8.731231550950663e-24, -8.611354408215601e-26,  1.773972524251053e-03,
 -2.419178408760504e-05,  2.749265199497571e-07, -2.916113289305358e-09,  2.982625864785823e-11, -2.982866239222104e-13,  2.937909782350371e-15, -2.861833803994014e-17,
  2.764497397297956e-19, -2.653017980432606e-21,  2.532634129056787e-23, -2.407031561393940e-25,  3.994067677913815e-04, -5.446737284511563e-06,  6.189921839946451e-08,
 -6.565577355188651e-10,  6.715329239319186e-12, -6.715870438105161e-14,  6.614651772780174e-16, -6.443368056965517e-18,  6.224216865174660e-20, -5.973222943782537e-22,
  5.702180877480223e-24, -5.419389092460535e-26,  1.681393472913476e-03, -2.212466241253874e-05,  2.426113184061508e-07, -2.483043503672835e-09,  2.450553383288385e-11,
 -2.364746478033278e-13,  2.247370453226597e-15, -2.112350649466161e-17,  1.968897797671093e-19, -1.823192646569138e-21,  1.679384724808393e-23, -1.540095247121580e-25,
  3.785627585666358e-04, -4.981328505298196e-06,  5.462350808117305e-08, -5.590528413093976e-10,  5.517377483243082e-12, -5.324184757800805e-14,  5.059914719554885e-16,
 -4.755920025933576e-18,  4.432938474423075e-20, -4.104885911999978e-22,  3.781104932466074e-24, -3.467497168752855e-26,  1.596596852106867e-03, -2.029663379893051e-05,
  2.150202269972860e-07, -2.126049355479371e-09,  2.027093967866433e-11, -1.889796206850931e-13,  1.735104789269163e-15, -1.575569991217307e-17,  1.418781446949547e-19,
 -1.269245180362859e-21,  1.129493648471315e-23, -1.000700724505039e-25,  3.594709497742208e-04, -4.569751104853577e-06,  4.841142278176642e-08, -4.786762419533351e-10,
  4.563966119242787e-12, -4.254842645217587e-14,  3.906557661901291e-16, -3.547367893356627e-18,  3.194361266533768e-20, -2.857683014447167e-22,  2.543034919690893e-24,
 -2.253059939167146e-26,  1.518696483769342e-03, -1.867328191461787e-05,  1.913358587343587e-07, -1.829829759218244e-09,  1.687452144878248e-11, -1.521572925004976e-13,
  1.351212666666485e-15, -1.186740848024219e-17,  1.033603275143684e-19, -8.943429344872932e-22,  7.697727429056161e-24, -6.596374478547233e-26,  3.419318199950915e-04,
 -4.204256307026823e-06,  4.307892927030669e-08, -4.119829251844776e-10,  3.799268578147794e-12, -3.425794456380843e-14,  3.042231355978351e-16, -2.671925973124413e-18,
  2.327139443600769e-20, -2.013597256347049e-22,  1.733129679315068e-24, -1.485162016245421e-26,  1.446931851449207e-03, -1.722605736981632e-05,  1.709028460927188e-07,
 -1.582527216229019e-09,  1.413056402139714e-11, -1.233696438782192e-13,  1.060783465295611e-15, -9.020828192445204e-18,  7.607323379759688e-20, -6.373376266751819e-22,
  5.311479164268176e-24, -4.407047190027845e-26,  3.257741402988833e-04, -3.878416267338733e-06,  3.847847271087756e-08, -3.563031962080570e-10,  3.181471429631173e-12,
 -2.777645652983068e-14,  2.388335159695547e-16, -2.031023469581252e-18,  1.712775367779763e-20, -1.434954363628171e-22,  1.195870114239727e-24, -9.922388592809519e-27
  };
  int offset = -2;
  for (int i = 1; i <= n; ++i) {
    double t = ta[i-1];
    offset += 2;
    if (t < 0.0) {
      fill_n(rr+offset, 2, 0.5);
      fill_n(ww+offset, 2, 0.0);
    } else if (t >= 64.0) {
      t = 1.0/sqrt(t);
      for (int r = 0; r != 2; ++r) {
        rr[offset+r] = ax[r]*t*t;
        ww[offset+r] = aw[r]*t*t*t;
      }
    } else {
      int it = static_cast<int>(t*   0.500000000000000);
      t = (t-it*2.000000000000000-   1.000000000000000) *   1.000000000000000;
      const double t2 = t * 2.0;
      for (int j=1; j <=2; ++j) {
        const int boxof = it*24+12*(j-1);
        double d = x[boxof+11];
        double e = w[boxof+11];
        double f = t2*d + x[boxof+10];
        double g = t2*e + w[boxof+10];
        d = t2*f - d + x[boxof+9];
        e = t2*g - e + w[boxof+9];
        f = t2*d - f + x[boxof+8];
        g = t2*e - g + w[boxof+8];
        d = t2*f - d + x[boxof+7];
        e = t2*g - e + w[boxof+7];
        f = t2*d - f + x[boxof+6];
        g = t2*e - g + w[boxof+6];
        d = t2*f - d + x[boxof+5];
        e = t2*g - e + w[boxof+5];
        f = t2*d - f + x[boxof+4];
        g = t2*e - g + w[boxof+4];
        d = t2*f - d + x[boxof+3];
        e = t2*g - e + w[boxof+3];
        f = t2*d - f + x[boxof+2];
        g = t2*e - g + w[boxof+2];
        d = t2*f - d + x[boxof+1];
        e = t2*g - e + w[boxof+1];
        rr[offset+j-1] = t*d - f + x[boxof+0]*0.5;
        ww[offset+j-1] = t*e - g + w[boxof+0]*0.5;
      }
    }
  }
}
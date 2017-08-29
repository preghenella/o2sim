// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \author R+Preghenella - August 2017

#ifdef __CINT__
 
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class o2::eventgen::MCEventHeader+;
#pragma link C++ class o2::eventgen::PrimaryGenerator+;
#pragma link C++ class o2::eventgen::Generator+;
#pragma link C++ class o2::eventgen::GeneratorHeader+;
#pragma link C++ class o2::eventgen::GeneratorHeaderInfo+;
#pragma link C++ class o2::eventgen::CrossSectionInfo+;
#pragma link C++ class o2::eventgen::GeneratorHepMC+;
#pragma link C++ class o2::eventgen::GeneratorTGenerator+;

#pragma link C++ class std::vector<GeneratorHeader *>
#pragma link C++ class std::map<std::string, GeneratorHeaderInfo *>+;

#pragma link C++ class o2sim::GeneratorManager+;
#pragma link C++ class o2sim::GeneratorManagerBox+;
#pragma link C++ class o2sim::GeneratorManagerPythia+;
#pragma link C++ class o2sim::GeneratorManagerHijing+;

#endif

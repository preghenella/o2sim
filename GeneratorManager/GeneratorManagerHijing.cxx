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

#include "GeneratorManagerHijing.h"
#include "Generators/Generator.h"
#include "THijing.h"
#include "TSystem.h"

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  GeneratorManagerHijing::GeneratorManagerHijing() :
    GeneratorManagerDelegate()
  {
    /** deafult constructor **/

    RegisterValue("energy", "5000");
    RegisterValue("b_range", "0.0, 20.0");
    RegisterValue("decay_table", "$ALICE_ROOT/data/hijingdecaytable.dat");
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerHijing::Init()
  {
    /** init **/

    /** check active **/
    if (!GetValue("status").Contains("active"))
      return kTRUE;

    /** create generator **/ 
    o2::eventgen::Generator *generator = new o2::eventgen::Generator();

    /** decay table environment variable **/
    TString decay_table = GetValue("decay_table");
    if (gSystem->ExpandPathName(decay_table)) {
      LOG(FATAL) << "Cannot expand \"" << "decay_table" << "\": " << decay_table << std::endl;
      return kFALSE;
    }
    gSystem->Setenv("HIJING_DECAY_TABLE", decay_table);
    
    /** check energy **/
    TString energy_str = GetValue("energy");
    if (!energy_str.IsDigit() && !energy_str.IsFloat()) {
      LOG(FATAL) << "Invalid energy: " << energy_str << std::endl;
      return kFALSE;
    }
    Float_t energy = energy_str.Atof();

    /** parse impact parameter range **/
    Float_t b[2];
    TString name = "b_range";
    if (!ParseValue(name, b, 2)) {
      LOG(FATAL) << "Cannot parse \"" << name << "\": " << GetValue(name) << std::endl;
      return kFALSE;
    }

    /** configure and initialise hijing interface **/
    gSystem->Load("libTHijing");
    THijing *hijing = new THijing(energy, "CMS     ", "A       ", "A       ", 208, 82, 208, 82, b[0], b[1]);
    hijing->SetIHPR2(2, 3);
    hijing->SetIHPR2(2, 0);
    hijing->SetIHPR2(6, 1);
    hijing->SetIHPR2(12, 3);
    hijing->SetIHPR2(21, 0);
    hijing->SetHIPR1(8, 2.0);
    hijing->SetHIPR1(9, -1.);
    hijing->SetHIPR1(10, -2.5);
    hijing->SetHIPR1(50, kFALSE);
    hijing->SetIHPR2(50, 0);
    hijing->SetIHPR2(4,  1);
    hijing->SetIHPR2(49, 0);
    hijing->SetIHPR2(31, 1);
    hijing->Initialize();
    
    /** configure generator **/
    generator->SetGenerator(hijing);

    /** success **/
    fGenerator = generator;
    return kTRUE;
  }
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

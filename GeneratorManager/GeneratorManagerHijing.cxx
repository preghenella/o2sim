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
#include "Generator.h"
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

    /** register values **/
    RegisterValue("b_range", "0.0, 20.0");

    /** default commands **/
    ProcessCommand("decay_table $O2SIM_ROOT/data/hijingdecaytable.dat");
  }

  /*****************************************************************/

  FairGenerator *
  GeneratorManagerHijing::Init() const
  {
    /** init **/

    /** decay table environment variable **/
    TString decay_table = GetValue("decay_table");
    if (gSystem->ExpandPathName(decay_table)) {
      LOG(FATAL) << "Cannot expand \"" << "decay_table" << "\": " << decay_table << std::endl;
      return NULL;
    }
    gSystem->Setenv("HIJING_DECAY_TABLE", decay_table);
    
    /** get energy **/
    Double_t energy;
    if (!GetCMSEnergy(energy)) return NULL;
    /** get projectile/target (A, Z) **/
    Int_t projectileA, projectileZ, targetA, targetZ;
    if (!GetBeamAZ("projectile", projectileA, projectileZ)) return NULL;
    if (!GetBeamAZ("target", targetA, targetZ)) return NULL;
    
    /** parse impact parameter range **/
    Double_t b[2];
    TString name = "b_range";
    if (!GetValue(name, b, 2)) {
      LOG(FATAL) << "Cannot parse \"" << name << "\": " << GetValue(name) << std::endl;
      return NULL;
    }

    /** configure and initialise hijing interface **/
    gSystem->Load("libTHijing");
    THijing *hij = new THijing(energy, "CMS     ", "A       ", "A       ",
			       projectileA, projectileZ,
			       targetA, targetZ,
			       b[0], b[1]);
    ConfigureBaseline(hij);
    hij->Initialize();
    
    /** create generator **/ 
    o2::eventgen::Generator *generator = new o2::eventgen::Generator();

    /** configure generator **/
    generator->SetGenerator(hij);

    /** success **/
    return generator;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerHijing::ConfigureBaseline(THijing *hij) const
  {
    /** configure baseline **/

    hij->SetIHPR2(2, 3);
    hij->SetIHPR2(2, 0);
    hij->SetIHPR2(6, 1);
    hij->SetIHPR2(12, 3);
    hij->SetIHPR2(21, 0);
    hij->SetHIPR1(8, 2.0);
    hij->SetHIPR1(9, -1.);
    hij->SetHIPR1(10, -2.5);
    hij->SetHIPR1(50, kFALSE);
    hij->SetIHPR2(50, 0);
    hij->SetIHPR2(4,  1);
    hij->SetIHPR2(49, 0);
    hij->SetIHPR2(31, 1);

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

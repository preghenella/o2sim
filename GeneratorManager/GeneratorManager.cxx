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

#include "GeneratorManager.h"
#include "GeneratorManagerDelegate.h"
#include "GeneratorManagerPythia6.h"
#include "GeneratorManagerHijing.h"
#include "FairRunSim.h"
#include "FairPrimaryGenerator.h"

namespace o2sim
{
  
  /*****************************************************************/
  /*****************************************************************/

  GeneratorManager::GeneratorManager() :
    ConfigurationManager(),
    fPrimaryGenerator(new FairPrimaryGenerator())
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("diamond_xyz", "0., 0., 0.");
    RegisterValue("diamond_sigma_xyz", "0., 0., 0.");
    
    /** register delegates **/
    RegisterDelegate("pythia6", new GeneratorManagerPythia6()); 
    RegisterDelegate("hijing", new GeneratorManagerHijing()); 
    
  }
  
  /*****************************************************************/
  
  Bool_t
  GeneratorManager::Init()
  {
    /** init **/
    
    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }
   
     /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<GeneratorManagerDelegate *>(x.second);
      if (!delegate) continue;
      if (!delegate->Init()) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return kFALSE;
      }
      auto generator = delegate->GetGenerator();
      if (!generator) continue;
      fPrimaryGenerator->AddGenerator(generator);
      LOG(INFO) << "Added generator from \"" << x.first << "\" delegate" << std::endl;
    }

    /** config primary generator **/
    if (!SetupInteractionDiamond()) return kFALSE;

    runsim->SetGenerator(fPrimaryGenerator);
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManager::SetupInteractionDiamond()
  {
    /** setup interaction diamond **/

    /** parse interaction diamond xyz, sigma_xyz **/
    Float_t xyz[3], sigma_xyz[3];
    TString name = "diamond_xyz";
    if (!ParseValue(name, xyz, 3)) {
      LOG(FATAL) << "Cannot parse \"" << name << "\": " << GetValue(name) << std::endl;
      return kFALSE;
    }
    name = "diamond_sigma_xyz";
    if (!ParseValue(name, sigma_xyz, 3)) {
      LOG(FATAL) << "Cannot parse \"" << name << "\": " << GetValue(name) << std::endl;
      return kFALSE;
    }
    /** set primary generator **/
    fPrimaryGenerator->SetBeam(xyz[0], xyz[1], sigma_xyz[0], sigma_xyz[1]);
    fPrimaryGenerator->SetTarget(xyz[2], sigma_xyz[2]);
    fPrimaryGenerator->SmearGausVertexXY(kTRUE);
    fPrimaryGenerator->SmearGausVertexZ(kTRUE);

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

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
#include "PrimaryGenerator.h"
#include "MCEventHeader.h"
#include "Core/GeneratorManagerDelegate.h"
#include "FairRunSim.h"
#include "FairPrimaryGenerator.h"

namespace o2sim
{
  
  /*****************************************************************/
  /*****************************************************************/

  GeneratorManager::GeneratorManager() :
    RunManagerDelegate()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("diamond_xyz", "0., 0., 0.");
    RegisterValue("diamond_sigma_xyz", "0., 0., 0.");
    RegisterValue("embed_into");
    
  }
  
  /*****************************************************************/
  
  Bool_t
  GeneratorManager::Init() const
  {
    /** init **/
    
    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }

    /** create primary generator **/
    o2eg::PrimaryGenerator *primGen = new o2eg::PrimaryGenerator();

    /** create MC event header **/
    o2eg::MCEventHeader *eventHeader = new o2eg::MCEventHeader();
    
    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<GeneratorManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      LOG(INFO) << "Initialising \"" << x.first << "\" manager (" << GetDelegateClassName(x.first) << ")" << std::endl;
      auto generator = delegate->Init();      
      if (!generator) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return kFALSE;
      }
      /** add generator **/
      primGen->AddGenerator(generator);
      LOG(INFO) << "Added generator from \"" << x.first << "\" delegate" << std::endl;
    }

    /** config primary generator **/
    if (!ConfigurePrimaryGenerator(primGen)) return kFALSE;

    /** add primary generator to FairRunSim instance **/
    runsim->SetGenerator(primGen);
    /** add MC event header to FairRunSim instance **/
    runsim->SetMCEventHeader(eventHeader);
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/
  
  Bool_t
  GeneratorManager::Terminate() const
  {
    /** terminate **/
    
    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }

    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<GeneratorManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      if (!delegate->Terminate()) {
	LOG(ERROR) << "Failed terminating \"" << x.first << "\" manager" << std::endl;
	return kFALSE;
      }
    }

    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManager::ConfigurePrimaryGenerator(o2eg::PrimaryGenerator *primGen) const
  {
    /** configure primary generator **/

    /** setup interaction diamond **/
    if (!SetupInteractionDiamond(primGen)) return kFALSE;

    /** check embed into **/
    if (!IsNull("embed_into")) {
      TString embed_into = GetValue("embed_into");
      if (gSystem->ExpandPathName(embed_into)) {
	LOG(FATAL) << "Cannot expand \"" << "embed_into" << "\": " << embed_into << std::endl;
	return kFALSE;
      }
      if (!primGen->EmbedInto(embed_into)) {
	LOG(FATAL) << "Cannot embed into " << embed_into << std::endl;
	return kFALSE;
      }
      LOG(INFO) << "Embedding into " << embed_into << std::endl;
    }
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManager::SetupInteractionDiamond(o2eg::PrimaryGenerator *primGen) const
  {
    /** setup interaction diamond **/

    /** parse interaction diamond xyz, sigmaxyz **/
    Double_t xyz[3], sigmaxyz[3];
    TString name = "diamond_xyz";
    if (!GetValue(name, xyz, 3)) {
      LOG(FATAL) << "Cannot parse \"" << name << "\": " << GetValue(name) << std::endl;
      return kFALSE;
    }
    name = "diamond_sigma_xyz";
    if (!GetValue(name, sigmaxyz, 3)) {
      LOG(FATAL) << "Cannot parse \"" << name << "\": " << GetValue(name) << std::endl;
      return kFALSE;
    }
    /** set primary generator **/
    primGen->SetInteractionDiamond(xyz, sigmaxyz);

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

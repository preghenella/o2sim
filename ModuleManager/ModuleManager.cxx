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

#include "ModuleManager.h"
#include "ModuleManagerDelegate.h"
#include "ModuleManagerCave.h"
#include "ModuleManagerTPC.h"
#include "FairRunSim.h"

namespace o2sim
{
  
  /*****************************************************************/
  /*****************************************************************/

  ModuleManager::ModuleManager() :
    RunManagerDelegate()
  {
    /** deafult constructor **/

    /** register values **/

    /** register delegates **/
    RegisterDelegate("cave", new ModuleManagerCave()); 
    RegisterDelegate("tpc", new ModuleManagerTPC()); 
    
  }
  
  /*****************************************************************/
  
  Bool_t
  ModuleManager::Init() const
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
      auto delegate = dynamic_cast<ModuleManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      auto module = delegate->Init();
      if (!module) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return kFALSE;
      }
      runsim->AddModule(module);
      LOG(INFO) << "Added module from \"" << x.first << "\" delegate" << std::endl;
    }
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/
  
  Bool_t
  ModuleManager::Terminate() const
  {
    /** terminate **/
    
    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<ModuleManagerDelegate *>(x.second);
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
  /*****************************************************************/
  
} /** namespace o2sim **/

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
    ConfigurationManager()
  {
    /** deafult constructor **/

    /** register values **/

    /** register delegates **/
    RegisterDelegate("cave", new ModuleManagerCave()); 
    RegisterDelegate("tpc", new ModuleManagerTPC()); 
    
  }
  
  /*****************************************************************/
  
  Bool_t
  ModuleManager::Init()
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
      if (!delegate) continue;
      if (!delegate->Init()) continue;
      auto module = delegate->GetModule();
      if (!module) continue;
      runsim->AddModule(module);
      LOG(INFO) << "Added module from \"" << x.first << "\" delegate" << std::endl;
    }
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

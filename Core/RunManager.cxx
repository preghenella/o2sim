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

#include "RunManager.h"
#include "FairRunSim.h"
#include "SimulationManager/SimulationManager.h"
#include "ModuleManager/ModuleManager.h"
#include "GeneratorManager/GeneratorManager.h"
#include <fstream>

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  RunManager::RunManager() :
    ConfigurationManager()
  {
    /** deafult constructor **/

  }

  /*****************************************************************/

  Bool_t
  RunManager::Init() const
  {
    /** init **/

    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }

    /** process buffered commands **/
    
    /** print status **/
    PrintStatus();

    /**
     ** WARNING: must ensure that simulation manager
     ** the first to be called or enforce order of initialisation
     **/

    std::cout << std::string(80, '-') << std::endl;
    LOG(INFO) << "Initialising \"" << "simulation" << "\" manager" << std::endl;
    auto delegate = dynamic_cast<RunManagerDelegate *>(GetDelegate("simulation"));
    if (!delegate || !delegate->IsActive() || !delegate->Init()) {
      LOG(ERROR) << "Failed initialising \"" << "simulation" << "\" manager" << std::endl;
      return kFALSE;
    }
    std::cout << std::string(80, '-') << std::endl;
    
    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      if (x.first.EqualTo("simulation")) continue; //R+hack
      auto delegate = dynamic_cast<RunManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      std::cout << std::string(80, '-') << std::endl;
      LOG(INFO) << "Initialising \"" << x.first << "\" manager (" << GetDelegateClassName(x.first) << ")" << std::endl;
      if (!delegate->Init()) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return kFALSE;
      }
      std::cout << std::string(80, '-') << std::endl;
    }

    /** init FairRunSim **/
    runsim->Init();
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  RunManager::Run() const
  {
    /** run **/

    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }

    auto simulation = dynamic_cast<SimulationManager *>(GetDelegate("simulation"));
    return simulation->Run();
  }
    
  /*****************************************************************/

  Bool_t
  RunManager::Terminate() const
  {
    /** terminate **/

    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<RunManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      LOG(INFO) << "Terminating \"" << x.first << "\" manager" << std::endl;
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
  
  Bool_t
  RunManager::ProcessCommand(TString command)
  {
    /** process command **/

    Bool_t retval = ConfigurationManager::ProcessCommand(command);
    if (!retval) {
      LOG(ERROR) << "\"" << command << "\" is not a valid command" << std::endl;
      exit(1);
    }
    return retval;
  }

  /*****************************************************************/

  Bool_t
  RunManager::ProcessFile(TString filename)
  {
    /** process file **/

    Bool_t retval = kTRUE;
    /** process delegates **/ 
    retval &= ConfigurationManager::ProcessFile(filename, kDelegates);
    /** process values **/ 
    retval &= ConfigurationManager::ProcessFile(filename, kValues);
    return retval;
  }

  /*****************************************************************/

  Bool_t
  RunManager::ProcessBuffer(std::vector<std::string> buffer)
  {
    /** process buffer **/

    Bool_t retval = kTRUE;
    /** process delegates **/
    for (auto const &command : buffer) {
      retval &= ConfigurationManager::ProcessCommand(command, kDelegates);
    }
    /** process values **/
    for (auto const &command : buffer) {
      retval &= ConfigurationManager::ProcessCommand(command, kValues);
    }
    /** return **/
    return retval;
  }

  /*****************************************************************/

  void
  RunManager::PrintStatus() const
  {
    /** print status **/
    
    std::cout << std::string(80, '-') << std::endl;
    ConfigurationManager::PrintStatus();
    std::cout << std::string(80, '-') << std::endl;
  }			

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

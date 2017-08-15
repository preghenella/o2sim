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
      LOG(INFO) << "Initialising \"" << x.first << "\" manager" << std::endl;
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

    /** open file **/
    std::ifstream fin(filename.Data());
    if (!fin.is_open()) {
      LOG(ERROR) << "Cannot open file " << filename << std::endl;
      return kFALSE;
    }

    /** process lines **/
    std::string whitespace = " \t\f\v\n\r";
    std::string comment = "#";
    Bool_t retval = kTRUE;
    for (std::string line; getline(fin, line);) {
      /** remove comments **/
      line = line.substr(0, line.find_first_of(comment));
      if (line.size() <= 0) continue;
      /** remove leading/trailing whitespaces **/
      const auto line_begin = line.find_first_not_of(whitespace);
      const auto line_end = line.find_last_not_of(whitespace);
      if (line_begin == std::string::npos ||
	  line_end == std::string::npos) continue;
      const auto line_range = line_end - line_begin + 1;
      line = line.substr(line_begin, line_range);
      if (line.size() <= 0) continue;
      /** process command **/
      TString command = line;
      retval &= ProcessCommand(command);
    }

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

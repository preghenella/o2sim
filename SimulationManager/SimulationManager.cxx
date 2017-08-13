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

#include "SimulationManager.h"
#include "FairRunSim.h"
#include "TSystem.h"

namespace o2sim
{
  
  /*****************************************************************/
  /*****************************************************************/

  SimulationManager::SimulationManager() :
    ConfigurationManager()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("vmc_path", "$VMCWORKDIR");
    RegisterValue("geometry_path", "Detectors/Geometry");
    RegisterValue("config_path", "Detectors/gconfig");
    RegisterValue("output_filename", "ALICEo2sim.output.root");
    RegisterValue("params_filename", "ALICEo2sim.params.root");
    RegisterValue("materials_filename", "media.geo");
    RegisterValue("mc_engine", "TGeant3");
    RegisterValue("nevents", "1");
    
    /** register delegates **/
    
  }
  
  /*****************************************************************/
  
  Bool_t
  SimulationManager::Init()
  {
    /** init **/

    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }

    /** setup environment **/
    if (!SetupEnvironment()) return kFALSE;
    
    /** setup more stuff **/
    runsim->SetName(GetValue("mc_engine"));
    runsim->SetOutputFile(GetValue("output_filename"));
    runsim->SetMaterials(GetValue("materials_filename"));
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  SimulationManager::SetupEnvironment()
  {
    /** setup environment **/

    /** expand paths **/
    std::map<TString, TString> path = {{"vmc_path", ""},
				       {"geometry_path", ""},
				       {"config_path", ""}};
    for (auto &x : path) {
      x.second = GetValue(x.first);
      if (gSystem->ExpandPathName(x.second)) {
	LOG(FATAL) << "Cannot expand \"" << x.first << "\": " << x.second << std::endl;
	return kFALSE;
      }
    }
    /** add VMC path to non-absolute paths **/
    for (auto &x : path) {
      if (x.first.EqualTo("vmc_path")) continue;
      if (x.second.BeginsWith("/")) continue;
      x.second = path["vmc_path"] + "/" + x.second;
    }

    /** set environment variables **/
    gSystem->Setenv("GEOMPATH", path["geometry_path"].Data());
    gSystem->Setenv("CONFIG_DIR", path["config_path"].Data());
        
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  
  Bool_t
  SimulationManager::Run()
  {
    /** run **/
    
    /** FairRunSim instance **/
    auto runsim = FairRunSim::Instance();
    if (!runsim) {
      LOG(FATAL) << "FairRunSim instance not created yet" << std::endl;
      return kFALSE;
    }

    /** get number of events **/
    Int_t nevents = -1;
    TString nevents_str = GetValue("nevents");
    if (!nevents_str.IsDigit()) {
      LOG(FATAL) << "Invalid number of events: " << nevents_str << std::endl;
      return kFALSE;
    }
    nevents = nevents_str.Atoi();
    
    /** run simulation **/
    runsim->Run(nevents);

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

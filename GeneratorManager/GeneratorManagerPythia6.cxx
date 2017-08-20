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

#include "GeneratorManagerPythia6.h"
#include "TriggerManager/TriggerManagerDelegate.h"
#include "Generator.h"
#include "TPythia6.h"
#include "TPythia6Decayer.h"
#include "TSystem.h"
#include "GeneratorHepMC.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  GeneratorManagerPythia6::GeneratorManagerPythia6() :
    GeneratorManagerDelegate()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("process", "minimum bias");
    RegisterValue("tune", "perugia 2011");
    RegisterValue("interface", "TPythia6");
  }

  /*****************************************************************/

  FairGenerator *
  GeneratorManagerPythia6::Init() const
  {
    /** init **/

    /** get energy **/
    Double_t energy;
    if (!GetCMSEnergy(energy)) return NULL;
    
    /** create config file **/
    std::string configFileName = "Pythia6." + std::string(GetName()) + ".param";
    std::ofstream config(configFileName, std::ofstream::out);
    /** configure **/
    config << "RG:Beam1 p+" << std::endl;
    config << "RG:Beam2 p+" << std::endl;
    config << "RG:Mom1 " << 0.5 * energy << std::endl;
    config << "RG:Mom2 " << 0.5 * energy << std::endl;
    ConfigureBaseline(config);
    ConfigureProcess(config);
    /** close config **/
    config.close();
    
    /** number of events **/
    Int_t nevents;
    if (!GetNumberOfEvents(nevents)) return NULL;

    /** create generators **/
    FairGenerator *generator = NULL;    
    if (IsValue("interface", "TPythia6")) generator = InitTPythia6(configFileName);
    else if (IsValue("interface", "AGILe")) generator = InitAGILe(configFileName);
    else return NULL;
    
    /** success **/
    return generator;
  }
  
  /*****************************************************************/

  FairGenerator *
  GeneratorManagerPythia6::InitTPythia6(std::string &configFileName) const
  {
    /** init TPythia6 **/

    /** configure and initialise pythia6 interface **/
    if (gSystem->Load("libpythia6") < 0) return NULL;
    TPythia6 *py6 = TPythia6::Instance();
    if (!py6) return NULL;

    /** read configuration **/
    TString projectile, target;
    Double_t energy = 0.;
    std::ifstream config(configFileName);
    if (!config.is_open()) return NULL;
    for (std::string line; getline(config, line);) {
      TString str = line;
      if (str.BeginsWith("RG:Beam1 ")) {
	str.Remove(0, TString("RG:Beam1 ").Sizeof() - 1);
	projectile = str;
      }
      else if (str.BeginsWith("RG:Beam2 ")) {
	str.Remove(0, TString("RG:Beam2 ").Sizeof() - 1);
	target = str;
      }
      if (str.BeginsWith("RG:Mom1 ")) {
	str.Remove(0, TString("RG:Mom1 ").Sizeof() - 1);
	energy += str.Atof();
      }
      else if (str.BeginsWith("RG:Mom2 ")) {
	str.Remove(0, TString("RG:Mom2 ").Sizeof() - 1);
	energy += str.Atof();
      }
      else if (str.BeginsWith("RG:")) continue;
      else py6->Pygive(line.c_str());
    }
    config.close();
    
    /** initialise TPythia6 interface **/     
    py6->Initialize("CMS", "p+", "p+", energy);
    
    /** create generator **/ 
    o2::eventgen::Generator *generator = new o2::eventgen::Generator();
    
    /** trigger mode **/
    o2::eventgen::Generator::ETriggerMode_t triggerMode = o2::eventgen::Generator::kTriggerOR;
    if (IsValue("trigger_mode", "OR")) triggerMode = o2::eventgen::Generator::kTriggerOR;
    if (IsValue("trigger_mode", "AND")) triggerMode = o2::eventgen::Generator::kTriggerAND;    
    
    /** configure generator **/
    generator->SetGenerator(py6);
    generator->SetTriggerMode(triggerMode);
    //    generator->SetNumberOfEvents(nevents);
    
    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<TriggerManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      LOG(INFO) << "Initialising \"" << x.first << "\" manager (" << GetDelegateClassName(x.first) << ")" << std::endl;
      auto trigger = delegate->Init();      
      if (!trigger) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return NULL;
      }
      /** add trigger **/
      generator->AddTrigger(trigger);
      LOG(INFO) << "Added trigger from \"" << x.first << "\" delegate" << std::endl;
    }

    /** success **/
    return generator;
  }

/*****************************************************************/

  FairGenerator *
  GeneratorManagerPythia6::InitAGILe(std::string &configFileName) const
  {
    /** init AGILe **/

    /** create fifo **/
    Char_t tmpname[1024];
    strncpy(tmpname, GetName(), 1024);
    std::string fifo_name = std::tmpnam(tmpname);
    if (mkfifo(fifo_name.c_str(), 0666) < 0) {
      LOG(ERROR) << "Could not create fifo: " << fifo_name << std::endl;
      return NULL;
    }

    /** preparation **/
    std::string agile_log = "AGILe." + std::string(GetName()) + ".log";
    std::string o2sim_path = getenv("O2SIM_ROOT");
    std::string agile_exe = "agile-pythia6.sh";
    std::string agile_cmd = o2sim_path + "/scripts/" + agile_exe;
    std::string agile_param = configFileName;
    std::string agile_out = fifo_name;

    /** create generator **/
    o2::eventgen::GeneratorHepMC *generator = new o2::eventgen::GeneratorHepMC();
    
    /** trigger mode **/
    o2::eventgen::Generator::ETriggerMode_t triggerMode = o2::eventgen::Generator::kTriggerOR;
    if (IsValue("trigger_mode", "OR")) triggerMode = o2::eventgen::Generator::kTriggerOR;
    if (IsValue("trigger_mode", "AND")) triggerMode = o2::eventgen::Generator::kTriggerAND;    
    
    /** configure generator **/
    generator->SetVersion(2);
    generator->SetFileName(fifo_name);
    
    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<TriggerManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      LOG(INFO) << "Initialising \"" << x.first << "\" manager (" << GetDelegateClassName(x.first) << ")" << std::endl;
      auto trigger = delegate->Init();      
      if (!trigger) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return NULL;
      }
      /** add trigger **/
      generator->AddTrigger(trigger);
      LOG(INFO) << "Added trigger from \"" << x.first << "\" delegate" << std::endl;
    }

    /** fork **/
    Int_t pid = fork();
    if (pid == 0) {
      /** redirect stdout/stderr **/
      Int_t fd = open(agile_log.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      dup2(fd, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      close(fd);
      /** execute agile-runmc **/
      Int_t ret = execl(agile_cmd.c_str(), agile_exe.c_str(), agile_param.c_str(), agile_out.c_str(), NULL);
      /** should not go here **/
      std::cout << "Unexpected return from execl: " << ret << std::endl;
      exit(1);
    }

    /** success **/
    return generator;
  }
 

/*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::Terminate() const
  {
    /** terminate **/

    if (IsValue("interface", "TPythia6")) return TerminateTPythia6();
    else if (IsValue("interface", "AGILe")) return TerminateAGILe();
    else return kFALSE;
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::TerminateTPythia6() const
  {
    /** terminate TPythia6 **/

    TPythia6 *py6 = TPythia6::Instance();
    if (!py6) return kFALSE;
    py6->Pystat(1);
    
    /** success **/
    return kTRUE;
    
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::TerminateAGILe() const
  {
    /** terminate AGILe **/

    /** success **/
    return kTRUE;
    
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::ConfigureBaseline(std::ostream &config) const
  {
    /** configure baseline **/

    /** parse tune **/
    Int_t tune = -1;
    TString tune_str = GetValue("tune");
    /** id **/
    if (tune_str.IsDigit())
      tune = tune_str.Atoi();
    /** default **/
    else if (tune_str.EqualTo("default", TString::kIgnoreCase))
      tune = kDefault;
    /** perugia 0 **/
    else if (tune_str.EqualTo("perugia0", TString::kIgnoreCase) ||
	     tune_str.EqualTo("perugia 0", TString::kIgnoreCase) ||
	     tune_str.EqualTo("perugia-0", TString::kIgnoreCase))
      tune = kPerugia0;
    /** perugia 2011 **/
    else if (tune_str.EqualTo("perugia2011", TString::kIgnoreCase) ||
	     tune_str.EqualTo("perugia 2011", TString::kIgnoreCase) ||
	     tune_str.EqualTo("perugia-2011", TString::kIgnoreCase))
      tune = kPerugia2011;
    /** unknown tune **/
    if (tune < 0) {
      LOG(ERROR) << "Unkown tune: " << tune_str << std::endl;
      return kFALSE;
    }

    /** config **/
    config << "MSTP(5) = " << tune << std::endl;
    config << "PMASS(4,1) = 1.275" << std::endl;
    config << "PMASS(5,1) = 4.66" << std::endl;
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::ConfigureProcess(std::ostream &config) const
  {
    /** configure process **/

    /** parse process **/
    Int_t process = -1;
    TString process_str = GetValue("process");
    /** id **/
    if (process_str.IsDigit())
      process = process_str.Atoi();
    /** default **/
    else if (process_str.EqualTo("default", TString::kIgnoreCase))
      process = kMinimumBias;
    /** minimum bias **/
    else if (process_str.EqualTo("minimum bias", TString::kIgnoreCase) ||
	     process_str.EqualTo("minimum-bias", TString::kIgnoreCase) ||
	     process_str.EqualTo("min.bias", TString::kIgnoreCase) ||
	     process_str.EqualTo("mb", TString::kIgnoreCase))
      process = kMinimumBias;
    /** jets **/
    else if (process_str.EqualTo("jets", TString::kIgnoreCase))
      process = kJets;
    /** direct gamma **/
    else if (process_str.EqualTo("direct gamma", TString::kIgnoreCase))
      process = kDirectGamma;
    /** charm **/
    else if (process_str.EqualTo("charm", TString::kIgnoreCase))
      process = kCharm;
    /** beauty **/
    else if (process_str.EqualTo("beauty", TString::kIgnoreCase))
      process = kBeauty;
    /** unknown process **/
    if (process < 0 || process >= kNProcesses) {
      LOG(ERROR) << "Unkown process: " << process_str << std::endl;
      return kFALSE;
    }

    /** select process **/
    switch (process) {

      /*****************************************************************/      
      
    case kMinimumBias:

      config << "MSEL = 0" << std::endl;
      config << "MSUB(92) = 1" << std::endl;
      config << "MSUB(93) = 1" << std::endl;
      config << "MSUB(94) = 1" << std::endl;
      config << "MSUB(95) = 1" << std::endl;

      return kTRUE;

      /*****************************************************************/

    case kJets:

      config << "MSEL = 1" << std::endl;
      
      return kTRUE;

      /*****************************************************************/
      
    case kDirectGamma:

      config << "MSEL = 10" << std::endl;
      
      return kTRUE;
      
      /*****************************************************************/
      
    case kCharm:
      
      config << "MSEL = 4" << std::endl;
      
      return kTRUE;
      
      /*****************************************************************/
      
    case kBeauty:
      
      config << "MSEL = 5" << std::endl;
      
      return kTRUE;
      
      /*****************************************************************/
      
    default:
      LOG(ERROR) << "Unknown process ID: " << process << std::endl;
      return kFALSE;
    }

    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

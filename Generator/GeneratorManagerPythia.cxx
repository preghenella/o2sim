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

#include "GeneratorManagerPythia.h"
#include "GeneratorHepMC.h"
#include "Core/TriggerManagerDelegate.h"
#include "TSystem.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  GeneratorManagerPythia::GeneratorManagerPythia() :
    GeneratorManagerDelegate()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("version", "pythia8");
    RegisterValue("process", "inelastic");
    RegisterValue("tune", "monash 2013");
    RegisterValue("pthat_min");
    RegisterValue("pthat_max", "-1");
    RegisterValue("decay_mode", "cylinder");
    RegisterValue("decay_xy", "1.");
    RegisterValue("decay_z", "100.");
    RegisterValue("decay_radius", "1.");
    RegisterValue("decay_ctau0");
    RegisterValue("decay_ctau");
  }

  /*****************************************************************/

  FairGenerator *
  GeneratorManagerPythia::Init() const
  {
    /** init **/

    /** get energy **/
    Double_t energy;
    if (!GetCMSEnergy(energy)) return NULL;
    
    /** create config **/
    std::string configFileName = std::string(GetValue("version").Data()) + "." + std::string(GetValue("name").Data()) + ".param";
    std::ofstream config(configFileName, std::ofstream::out);
    if (!ConfigureCollision(config)) {
      LOG(ERROR) << "Failed to configure generator collision system" << std::endl;
      return NULL;
    }
    if (!ConfigureBaseline(config)) {
      LOG(ERROR) << "Failed to configure generator baseline" << std::endl;
      return NULL;
    }
    if (!ConfigureTune(config)) {
      LOG(ERROR) << "Failed to configure generator tune" << std::endl;
      return NULL;
    }
    if (!ConfigureProcess(config)) {
      LOG(ERROR) << "Failed to configure generator process" << std::endl;
      return NULL;
    }
    /** close config **/
    config.close();
    
    /** number of events **/
    Int_t nevents;
    if (!GetNumberOfEvents(nevents)) return NULL;

    /** create generator **/
    o2::eventgen::GeneratorHepMC *generator = new o2::eventgen::GeneratorHepMC();    

    /** init trigger **/
    if (!InitTrigger(generator)) {
      LOG(ERROR) << "Failed to initialise generator trigger" << std::endl;
      return NULL;
    }
    
    /** init interface **/
    Int_t pid;
    if (!InitInterface(generator, configFileName, pid)) {
      LOG(ERROR) << "Failed to initialise generator interface" << std::endl;
      return NULL;
    }
    
    /** success **/
    return generator;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::ConfigureCollision(std::ostream &config) const
  {
    /** configure collision **/

    /** get energy **/
    Double_t energy;
    if (!GetCMSEnergy(energy)) return kFALSE;

    /** configure **/
    
    /** pythia6 **/
    if (IsValue("version", "pythia6")) {
      config << "RG:Beam1 2212" << std::endl;
      config << "RG:Beam2 2212" << std::endl;
      config << "RG:Mom1 " << 0.5 * energy << std::endl;
      config << "RG:Mom2 " << 0.5 * energy << std::endl;
    }
    /** pythia8 **/
    else if (IsValue("version", "pythia8")) {
      config << "Beams:idA 2212" << std::endl;
      config << "Beams:idB 2212" << std::endl;
      config << "Beams:frameType 1" << std::endl;
      config << "Beams:eCM " << energy << std::endl;
    }
    /** unknown **/
    else return kFALSE;
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::ConfigureBaseline(std::ostream &config) const
  {
    /** configure baseline **/


    /*****************************************************************/      
    /* HEAVY-QUARK MASSES                                            */
    /*****************************************************************/      
    
    /** pythia6 **/
    if (IsValue("version", "pythia6")) {
      config << "PMASS(4,1) = 1.27" << std::endl; // charm mass
      config << "PMASS(5,1) = 4.18" << std::endl; // beauty mass
    }
    /** pythia8 **/
    else if (IsValue("version", "pythia8")) {
      config << "ParticleData:mcRun 1.27" << std::endl; // charm mass
      config << "ParticleData:mbRun 4.18" << std::endl; // beauty mass
    }
    /** unknown **/
    else return kFALSE;
    
    /*****************************************************************/      
    /* DECAYS GENERAL                                                */
    /*****************************************************************/      
    
    /** default particle decays **/

    if (IsValue("decay_mode", "default")) {
    }
    
    /*****************************************************************/      

    /** all particle decays are inhibited **/

    if (IsValue("decay_mode", "none")) {
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSTJ(21) = 0" << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	LOG(ERROR) << "Unsupported inhibit all particle decays in Pythia8" << std::endl;
	return kFALSE;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      

    /** only particles with tau0 < tau0Max are decayed **/ 
    
    else if (IsValue("decay_mode", "ctau0")) {
      /** check values **/
      Double_t decay_ctau0; // [cm]
      if (!GetValue("decay_ctau0", decay_ctau0)) return kFALSE;
      Double_t decay_tau0 = decay_ctau0 * 10. / TMath::C() ; // [mm/c]
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSTJ(22) = 2" << std::endl;
	config << "PARJ(71) = " << decay_tau0 << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "ParticleDecays:limitTau0 on" << std::endl;
	config << "ParticleDecays:tau0Max " << decay_tau0 << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      

    /** only particles with tau < tauMax are decayed **/ 
    
    else if (IsValue("decay_mode", "ctau")) {
      /** check values **/
      Double_t decay_ctau; // [cm]
      if (!GetValue("decay_ctau", decay_ctau)) return kFALSE;
      Double_t decay_tau = decay_ctau * 10.; // [mm/c]
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	LOG(ERROR) << "Unsupported tau < tauMax particle decays in Pythia6" << std::endl;
	return kFALSE;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "ParticleDecays:limitTau on" << std::endl;
	config << "ParticleDecays:tauMax " << decay_tau << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      

    /** only particles with a decay within a radius r < rMax are decayed **/
    
    else if (IsValue("decay_mode", "radius")) {
      /** check values **/
      Double_t decay_radius; // [cm]
      if (!GetValue("decay_radius", decay_radius)) return kFALSE;
      decay_radius *= 10.; // [mm]
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {	
	config << "MSTJ(22) = 3" << std::endl;
	config << "PARJ(72) = " << decay_radius << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "ParticleDecays:limitRadius on" << std::endl;
	config << "ParticleDecays:rMax " << decay_radius << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      

    /** only particles with a decay within a volume limited by 
	rho = sqrt(x^2 + y^2) < xyMax and |z| < zMax are decayed **/
    
    else if (IsValue("decay_mode", "cylinder")) {
      /** check values **/
      Double_t decay_xy, decay_z;
      if (!GetValue("decay_xy", decay_xy) || !GetValue("decay_z", decay_z)) return kFALSE;
      decay_xy *= 10.; // [mm]
      decay_z *= 10.; // [mm]
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {		
	config << "MSTJ(22) = 4" << std::endl;
	config << "PARJ(73) = " << decay_xy << std::endl;
	config << "PARJ(74) = " << decay_z << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "ParticleDecays:limitCylinder on" << std::endl;
	config << "ParticleDecays:xyMax " << decay_xy << std::endl;
	config << "ParticleDecays:zMax " << decay_z << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      

    /** unknown decay mode **/
    else return kFALSE;
    
    /*****************************************************************/      
    /* DECAYS SPECIAL                                                */
    /*****************************************************************/      

    /** pythia6 **/
    if (IsValue("version", "pythia6")) {		
    }
    /** pythia8 **/
    else if (IsValue("version", "pythia8")) {
      config << "111:mayDecay = false" << std::endl; // inhibit pi0 decay
    }      
    /** unknown **/
    else return kFALSE;
    
    /*****************************************************************/      
    /* DONE                                                          */
    /*****************************************************************/      

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::ConfigureTune(std::ostream &config) const
  {
    /** configure tune **/

    /*****************************************************************/      
    /* TUNE ID                                                       */
    /*****************************************************************/      
    
    Int_t tune;
    if (GetValue("tune", tune)) {
      if (IsValue("version", "pythia6"))
	config << "MSTP(5) = " << tune << std::endl;	
      if (IsValue("version", "pythia8"))
	config << "Tune:pp " << tune << std::endl;
    }

    /*****************************************************************/      
    /* DEFAULT                                                       */
    /*****************************************************************/      
    
    else if (IsValue("tune", "default")) {
      if (IsValue("version", "pythia6"))
	config << "MSTP(5) = 0" << std::endl;	
      if (IsValue("version", "pythia8"))
	config << "Tune:pp 0" << std::endl;
    }
      
    /*****************************************************************/      
    /* PYTHIA6 PERUGIA 0                                             */
    /*****************************************************************/      
    
    else if (IsValue("version", "pythia6") &&
	     (IsValue("tune", "perugia0") ||
	      IsValue("tune", "perugia 0") ||
	      IsValue("tune", "perugia-0"))) {
      config << "MSTP(5) = 320" << std::endl;
    }
    
    /*****************************************************************/      
    /* PYTHIA6 PERUGIA 2011                                          */
    /*****************************************************************/      
    
    else if (IsValue("version", "pythia6") &&
	     (IsValue("tune", "perugia2011") ||
	      IsValue("tune", "perugia 2011") ||
	      IsValue("tune", "perugia-2011"))) {
      config << "MSTP(5) = 350" << std::endl;
    }

    /*****************************************************************/      
    /* PYTHIA8 MONASH 2013                                           */
    /*****************************************************************/      
    
    else if (IsValue("version", "pythia8") &&
	     (IsValue("tune", "monash2013") ||
	      IsValue("tune", "monash 2013") ||
	      IsValue("tune", "monash-2013"))) {
      config << "Tune:pp 14" << std::endl;
    }

    /*****************************************************************/      
    /* UNKNOWN                                                       */
    /*****************************************************************/      
    
    else {
      LOG(ERROR) << "Unkown tune: " << GetValue("tune") << std::endl;
      return kFALSE;
    }

    /*****************************************************************/      
    /* DONE                                                          */
    /*****************************************************************/      

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::ConfigureProcess(std::ostream &config) const
  {
    /** configure process **/

    /** select process **/
    if (IsValue("process", "default")) return kFALSE;
    
    /*****************************************************************/      
    /* INELASTIC                                                     */
    /*****************************************************************/      
    
    else if (IsValue("process", "inelastic")) {
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSEL = 0" << std::endl;
	config << "MSUB(92) = 1" << std::endl;
	config << "MSUB(93) = 1" << std::endl;
	config << "MSUB(94) = 1" << std::endl;
	config << "MSUB(95) = 1" << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "SoftQCD:inelastic on" << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      
    /* JETS                                                          */
    /*****************************************************************/      

    else if (IsValue("process", "jets")) {
      /** check pT-hat **/
      Double_t pthat_min, pthat_max;
      if (!GetPtHat(pthat_min, pthat_max)) return kFALSE;
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSEL = 1" << std::endl;
	config << "CKIN(3) = " << pthat_min << std::endl;
	config << "CKIN(4) = " << pthat_max << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "HardQCD:all on" << std::endl;
	config << "PhaseSpace:pTHatMin " << pthat_min << std::endl;
	config << "PhaseSpace:pTHatMin " << pthat_max << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
    
    /*****************************************************************/      
    /* PROMPT PHOTONS                                                */
    /*****************************************************************/      

    else if (IsValue("process", "prompt photon")) {    
      /** check pT-hat **/
      Double_t pthat_min, pthat_max;
      if (!GetPtHat(pthat_min, pthat_max)) return kFALSE;
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSEL = 10" << std::endl;
	config << "CKIN(3) = " << pthat_min << std::endl;
	config << "CKIN(4) = " << pthat_max << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "PromptPhoton:all on" << std::endl;
	config << "PhaseSpace:pTHatMin " << pthat_min << std::endl;
	config << "PhaseSpace:pTHatMin " << pthat_max << std::endl;
      }
      /** success **/
      return kTRUE;
    }
      
    /*****************************************************************/      
    /* CHARM                                                         */
    /*****************************************************************/      
      
    else if (IsValue("process", "charm")) {    
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSEL = 4" << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "HardQCD:hardccbar on" << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
      
    /*****************************************************************/      
    /* BEAUTY                                                        */
    /*****************************************************************/      
      
    else if (IsValue("process", "charm")) {          
      /** pythia6 **/
      if (IsValue("version", "pythia6")) {
	config << "MSEL = 5" << std::endl;
      }
      /** pythia8 **/
      else if (IsValue("version", "pythia8")) {
	config << "HardQCD:hardbbbar on" << std::endl;
      }
      /** unknown **/
      else return kFALSE;
    }
      
    /*****************************************************************/      
    /* UNKNOWN                                                       */
    /*****************************************************************/      

    else {
      LOG(ERROR) << "Unknown process: " << GetValue("process") << std::endl;
      return kFALSE;
    }
    
    /*****************************************************************/      
    /* DONE                                                          */
    /*****************************************************************/      

    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::GetPtHat(Double_t &min, Double_t &max) const
  {
    /** get pT-hat **/

    /** check values **/
    if (!GetValue("pthat_min", min) ||
	!GetValue("pthat_max", max) ||
	min <= 0. ||
	(max > 0. && max <= min)) {
      LOG(ERROR) << "Invalid pT-hat (min,max): (" << GetValue("pthat_min") << "," << GetValue("pthat_max") << ")" << std::endl;
      return kFALSE;
    }
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::InitTrigger(o2::eventgen::GeneratorHepMC *generator) const
  {
    /** init trigger **/

    /** check trigger mode **/
    o2::eventgen::GeneratorHepMC::ETriggerMode_t triggerMode;
    if (IsNull("trigger_mode") || IsValue("trigger_mode", "OFF")) return kTRUE;
    else if (IsValue("trigger_mode", "OR")) triggerMode = o2::eventgen::GeneratorHepMC::kTriggerOR;
    else if (IsValue("trigger_mode", "AND")) triggerMode = o2::eventgen::GeneratorHepMC::kTriggerAND;
    else {
      LOG(ERROR) << "Invalid trigger_mode: " << GetValue("trigger_mode") << std::endl;
      return kFALSE;
    }
    generator->SetTriggerMode(triggerMode);
    
    /** loop over all delegates **/
    for (auto const &x : DelegateMap()) {
      auto delegate = dynamic_cast<TriggerManagerDelegate *>(x.second);
      if (!delegate || !delegate->IsActive()) continue;
      LOG(INFO) << "Initialising \"" << x.first << "\" manager (" << GetDelegateClassName(x.first) << ")" << std::endl;
      auto trigger = delegate->Init();      
      if (!trigger) {
	LOG(ERROR) << "Failed initialising \"" << x.first << "\" manager" << std::endl;
	return kFALSE;
      }
      /** add trigger **/
      generator->AddTrigger(trigger);
      LOG(INFO) << "Added trigger from \"" << x.first << "\" delegate" << std::endl;
    }

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::InitInterface(o2::eventgen::GeneratorHepMC *generator, std::string &configFileName, Int_t &pid) const
  {
    /** init interface **/

    /** create fifo **/
    Char_t tmpname[1024];
    strncpy(tmpname, GetValue("name"), 1024);
    std::string fifoName = std::tmpnam(tmpname);
    if (mkfifo(fifoName.c_str(), 0666) < 0) {
      LOG(ERROR) << "Could not create fifo: " << fifoName << std::endl;
      return kFALSE;
    }

    /** configure generator **/
    generator->SetVersion(2);
    generator->SetFileName(fifoName);
    
    /** preparation **/
    std::string exe;
    if (IsValue("version", "Pythia6")) exe = "agile-pythia6.sh";
    else if (IsValue("version", "Pythia8")) exe = "sacrifice-pythia8.sh";
    else return kFALSE;
    std::string path = getenv("O2SIM_ROOT");
    std::string cmd = path + "/scripts/" + exe;
    std::string param = configFileName;
    std::string out = fifoName;
    std::string log = std::string(GetValue("version").Data()) + "." +  std::string(GetValue("name").Data()) + ".log";

    /** fork **/
    pid = fork();
    if (pid == 0) {
      /** redirect stdout/stderr **/
      Int_t fd = open(log.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      dup2(fd, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      close(fd);
      /** execute **/
      Int_t ret = execl(cmd.c_str(), exe.c_str(), param.c_str(), out.c_str(), NULL);
      /** should not go here **/
      std::cout << "Unexpected return from execl: " << ret << std::endl;
      exit(1);
    }
    LOG(INFO) << "Interface process " << exe << " started: " << pid << std::endl; 
    
    /** success **/
    return generator;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia::Terminate() const
  {
    /** terminate **/

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

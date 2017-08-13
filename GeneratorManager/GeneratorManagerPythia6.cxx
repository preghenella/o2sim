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
#include "Generators/Generator.h"
#include "TPythia6.h"
#include "TSystem.h"

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  GeneratorManagerPythia6::GeneratorManagerPythia6() :
    GeneratorManagerDelegate()
  {
    /** deafult constructor **/

    RegisterValue("process", "minimum bias");
    RegisterValue("tune", "perugia 2011");
    RegisterValue("energy", "13000");
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::Init()
  {
    /** init **/

    /** check active **/
    if (!GetValue("status").Contains("active"))
      return kTRUE;

    /** create generator **/ 
    o2::eventgen::Generator *generator = new o2::eventgen::Generator();

    /** configure and initialise pythia6 interface **/
    gSystem->Load("libpythia6");
    TPythia6 *py6 = TPythia6::Instance();
    ConfigureBaseline(py6);
    ConfigureProcess(py6);
    /** check energy **/
    TString energy_str = GetValue("energy");
    if (!energy_str.IsDigit() && !energy_str.IsFloat()) {
      LOG(FATAL) << "Invalid energy: " << energy_str << std::endl;
      return kFALSE;
    }
    Float_t energy = energy_str.Atof();
    py6->Initialize("CMS", "p+", "p+", energy);
    
    /** configure generator **/
    generator->SetGenerator(py6);

    /** success **/
    fGenerator = generator;
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::ConfigureBaseline(TPythia6 *py6)
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
    py6->SetMSTP(5, tune);    // tune selection
    py6->SetPMAS(4, 1, 1.275); // charm quark mass
    py6->SetPMAS(5, 1, 4.66);  // beauty quark mass
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerPythia6::ConfigureProcess(TPythia6 *py6)
  {
    /** configure process **/

    /** reset subprocesses **/
    for (Int_t isub = 0; isub < 200; isub++)
      py6->SetMSUB(isub + 1, 0);

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
      
    case kMinimumBias:
      py6->SetMSEL(0);
      py6->SetMSUB(92, 1); // Single diffractive (XB)
      py6->SetMSUB(93, 1); // Single diffractive (AX)
      py6->SetMSUB(94, 1); // Double  diffractive
      py6->SetMSUB(95, 1); // Low-pT scattering
      return kTRUE;

    case kJets:
      py6->SetMSEL(1); // QCD high-pT processes
      //      py6->SetCKIN(3, fPtHardMin);
      //      py6->SetCKIN(4, fPtHardMax);
      //      py6->SetCKIN(7, fYMin);
      //      py6->SetCKIN(8, fYMax);
      return kTRUE;

    case kDirectGamma:
      py6->SetMSEL(10); // Prompt photon production
      return kTRUE;

    case kCharm:
      py6->SetMSEL(4); // Heavy flavours (charm)
      return kTRUE;
      
    case kBeauty:
      py6->SetMSEL(5); // Heavy flavours (beauty)
      return kTRUE;
      
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

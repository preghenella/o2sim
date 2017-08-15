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

#include "ConfigurationManager.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"
#include <iostream>
#include <iomanip>

#define PROCESSCOMMAND_VERBOSE 0

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/

  TString ConfigurationManager::fgPrependCommand;
  
  /*****************************************************************/

  ConfigurationManager::ConfigurationManager() :
    TObject()
  {
    /** deafult constructor **/

    RegisterValue("status", "...");
  }
  
  /*****************************************************************/

  Bool_t
  ConfigurationManager::RegisterValue(TString name, value_t value)
  {
    /** register value **/

    if (ValidValue(name)) {
      printf(">>>>> %s value already exists \n ", name.Data());
      return kFALSE;
    }
    fValue[name] = value;
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  ConfigurationManager::RegisterDelegate(TString name, delegate_t *delegate)
  {
    /** register delegate **/

    if (fDelegate.count(name)) {
      printf(">>>>> %s delegate already exists \n ", name.Data());
      return kFALSE;
    }
    fDelegate[name] = delegate;
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  ConfigurationManager::ProcessCommand(TString command)
  {
    /** process command **/

    /** initial adjustments **/
    TObjArray *oa = command.Tokenize(" \t");
    TString name = ((TObjString *)oa->At(0))->GetString();
    TString args;
    for (Int_t i = 0; i < oa->GetEntries(); i++) {
      if (i == 0) {
	command = ((TObjString *)oa->At(i))->GetString();
	continue;
      }
      command += " " + ((TObjString *)oa->At(i))->GetString();
      if (i == 1) {
	args = ((TObjString *)oa->At(i))->GetString();
	continue;
      }
      args += " " + ((TObjString *)oa->At(i))->GetString();
    }
    oa = name.Tokenize(".");
    TString value = ((TObjString *)oa->At(0))->GetString();

#if PROCESSCOMMAND_VERBOSE
    std::cout << "[" << this->ClassName() << "]" << " process command \"" << command << "\"" << std::endl;
#endif
    
    /** add prepend command **/
    if (command.BeginsWith(".")) {
      command = fgPrependCommand + command;
      return ProcessCommand(command);
    }

    /** change prepend command **/
    if (args.IsNull()) {
      fgPrependCommand = command;
#if PROCESSCOMMAND_VERBOSE
      std::cout << "[" << this->ClassName() << "[" << " change prepend: " << fgPrependCommand << std::endl;
#endif
      return kTRUE;
    }

    /** commands to be forwarded to delegate **/
    if (oa->GetEntries() > 1) {
      command.Remove(0, value.Sizeof());
      /** send command to all delegates **/
      if (value.EqualTo("*")) {
	Bool_t retval = kTRUE;
	/** loop over all delegates **/
	for (auto const &x : DelegateMap()) {
	  auto delegate = x.second;
	  if (!delegate) continue;
#if PROCESSCOMMAND_VERBOSE
	  std::cout << "[" << this->ClassName() << "]" << " forward to \"" << value << "\" delegate: \"" << command << "\"" << std::endl;
#endif
	  retval &= delegate->ProcessCommand(command); 
	}
	return retval;
      }
      if (!fDelegate.count(value)) return kFALSE;
#if PROCESSCOMMAND_VERBOSE
      std::cout << "[" << this->ClassName() << "]" << " forward to \"" << value << "\" delegate: \"" << command << "\"" << std::endl;
#endif
      return GetDelegate(value)->ProcessCommand(command);
    }
    
    /** value modification **/
#if PROCESSCOMMAND_VERBOSE
    std::cout << "[" << this->ClassName() << "]" << " change \"" << value << "\" value: \"" << args << "\"" << std::endl;
#endif
    if (!ValidValue(value)) return kFALSE;
    fValue[value] = args;

    /** success **/
    NotifyUpdate(value, args);
    return kTRUE;
  }

  /*****************************************************************/

  void
  ConfigurationManager::PrintStatus(TString prepend) const
  {
    /** print **/

    /** do not print if not active **/
    if (!IsActive()) return;
    
    Int_t width = 40;
    for (auto const &x : fValue) {
      std::cout << std::setw(width) << std::setfill(' ') << std::left << prepend + x.first << std::right << x.second << std::endl;
    }
    for (auto const &x : fDelegate)
      x.second->PrintStatus(prepend + x.first + ".");
    
    
  }
  
  /*****************************************************************/

  Bool_t
  ConfigurationManager::ParseValue(TString name, Double_t *ret, Int_t n) const
  {
    /** parse value **/

    if (!ValidValue(name)) return kFALSE;
    TString str = GetValue(name);
    str.ReplaceAll(",", " ");
    TObjArray *oa = str.Tokenize(" \t");
    if (oa->GetEntries() != n) return kFALSE;
    for (Int_t i = 0; i < n; i++) {
      TObjString *os = (TObjString *)oa->At(i);
      ret[i] = os->String().Atof();
    }

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  ConfigurationManager::ParseValue(TString name, Int_t *ret, Int_t n) const
  {
    /** parse value **/

    if (!ValidValue(name)) return kFALSE;
    TString str = GetValue(name);
    str.ReplaceAll(",", " ");
    TObjArray *oa = str.Tokenize(" \t");
    if (oa->GetEntries() != n) return kFALSE;
    for (Int_t i = 0; i < n; i++) {
      TObjString *os = (TObjString *)oa->At(i);
      ret[i] = os->String().Atoi();
    }

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

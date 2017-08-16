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
#include "TSystem.h"
#include "TROOT.h"
#include "TClass.h"

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

    RegisterValue("status", "active");
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
  ConfigurationManager::RegisterDelegate(TString name, delegate_t *delegate, TClass *delegate_class)
  {
    /** register delegate **/

    if (fDelegate.count(name)) {
      printf(">>>>> %s delegate already exists \n ", name.Data());
      return kFALSE;
    }
    fDelegate[name] = delegate;
    fDelegateClass[name] = delegate_class;
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  ConfigurationManager::ProcessCommand(TString command, EProcessCommand_t processMask)
  {
    /** process command **/

    /** initial adjustments **/
    command.ReplaceAll(",", " ");
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
      return ProcessCommand(command, processMask);
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
	  retval &= delegate->ProcessCommand(command, processMask); 
	}
	return retval;
      }
      if (!fDelegate.count(value)) return kFALSE;
#if PROCESSCOMMAND_VERBOSE
      std::cout << "[" << this->ClassName() << "]" << " forward to \"" << value << "\" delegate: \"" << command << "\"" << std::endl;
#endif
      return GetDelegate(value)->ProcessCommand(command, processMask);
    }

    /** special delegate() command **/
    if (value.EqualTo("delegate()")) {
      if (!(processMask & kDelegates)) return kTRUE;
      oa = args.Tokenize(" \t");
      if (oa->GetEntries() != 2) return kFALSE;
      TString delegate_name = ((TObjString *)oa->At(0))->GetString();
      TString delegate_class_name = ((TObjString *)oa->At(1))->GetString();
      if (!delegate_class_name.BeginsWith("o2sim::"))
	delegate_class_name = "o2sim::" + delegate_class_name;
      TClass *delegate_class = gROOT->GetClass(delegate_class_name);
#if PROCESSCOMMAND_VERBOSE
      std::cout << "[" << this->ClassName() << "]" << " delegate \"" << delegate_name << "\" to \"" << delegate_class_name << "\"" << std::endl;
#endif      
      if (!delegate_class) return kFALSE;
      auto delegate = (ConfigurationManager *)delegate_class->New();
      if (!delegate) return kFALSE;
      return RegisterDelegate(delegate_name, delegate, delegate_class);
    }
      
    /** special include() command **/
    if (value.EqualTo("include()")) {
      oa = args.Tokenize(" \t");
      if (oa->GetEntries() != 1) return kFALSE;
      TString filename = ((TObjString *)oa->At(0))->GetString();
      return ProcessFile(filename, processMask);
    }

    /** value modification **/
    if (processMask & kValues) {
#if PROCESSCOMMAND_VERBOSE
      std::cout << "[" << this->ClassName() << "]" << " change \"" << value << "\" value: \"" << args << "\"" << std::endl;
#endif
      if (!ValidValue(value)) return kFALSE;
      fValue[value] = args;
    }
    
    /** success **/
    NotifyUpdate(value, args);
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  ConfigurationManager::ProcessFile(TString filename, EProcessCommand_t processMask)
  {
    /** process file **/

    /** open file **/
    gSystem->ExpandPathName(filename);
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
      if (!ProcessCommand(command, processMask)) {
	LOG(ERROR) << "\"" << command << "\" is not a valid command" << std::endl;
	return kFALSE;
      }
    }

    /** success **/
    return retval;
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
    for (auto const &x : fDelegate) {
      /** print only for active delegates **/
      if (!x.second->IsActive()) continue;
      std::cout << "### " << prepend + x.first << " delegate" << std::endl;
      std::cout << std::setw(width) << std::setfill(' ') << std::left << prepend + "delegate()" << std::right << x.first << " " << fDelegateClass.at(x.first)->GetName() << std::endl;
      x.second->PrintStatus(prepend + x.first + ".");
    }
    
  }
  
  /*****************************************************************/

  Bool_t
  ConfigurationManager::GetValue(TString name, Int_t *v, Int_t n) const
  {
    /** get value **/

    /** check values **/
    if (!ValidValue(name)) return kFALSE;
    TString str = GetValue(name);
    TObjArray *oa = str.Tokenize(" \t");
    if (oa->GetEntries() != n) return kFALSE;
    for (Int_t i = 0; i < n; i++) {
      TObjString *os = (TObjString *)oa->At(i);
      TString val = os->String();
      if (!val.IsFloat() && !val.IsDigit()) return kFALSE;
      v[i] = val.Atoi();
    }
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  ConfigurationManager::GetValue(TString name, Double_t *v, Int_t n) const
  {
    /** get value **/

    /** check values **/
    if (!ValidValue(name)) return kFALSE;
    TString str = GetValue(name);
    TObjArray *oa = str.Tokenize(" \t");
    if (oa->GetEntries() != n) return kFALSE;
    for (Int_t i = 0; i < n; i++) {
      TObjString *os = (TObjString *)oa->At(i);
      TString val = os->String();
      if (!val.IsFloat() && !val.IsDigit()) return kFALSE;
      v[i] = val.Atof();
    }
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

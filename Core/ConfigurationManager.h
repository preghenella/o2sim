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

#ifndef ALICEO2SIM_CONFIGURATIONMANAGER_H_
#define ALICEO2SIM_CONFIGURATIONMANAGER_H_

#include "TObject.h"
#include "TString.h"
#include "FairLogger.h"
#include <map>
#include <iostream>

class TString;
class TClass;

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class ConfigurationManager : public TObject
  {

  public:

    /** typedefs **/
    typedef TString value_t;
    typedef ConfigurationManager delegate_t;
    typedef std::map<TString, value_t> value_map_t;
    typedef std::map<TString, delegate_t *> delegate_map_t;

    /** default constructor/destructor **/
    ConfigurationManager();

    /** methods **/
    Bool_t IsActive() const {return IsValue("status", "active");};
    
  protected:

    enum EProcessCommand_t {
      kNone      = 0x0,
      kDelegates = 0x1,
      kValues    = 0x2,
      kAll       = 0x3
    };

    /** methods **/
    virtual Bool_t ProcessCommand(TString command, EProcessCommand_t processMask = kAll);
    virtual Bool_t ProcessFile(TString filename, EProcessCommand_t processMask = kAll);
    void PrintStatus(TString prepend = "") const;

    Bool_t RegisterValue(TString name, value_t value = "");

    Bool_t ValidValue(TString name) const {return fValue.count(name) == 1;};
    value_t GetValue(TString name) const {return fValue.at(name);};
    Bool_t GetValue(TString name, Double_t *v, Int_t n) const;
    Bool_t GetValue(TString name, Int_t *v, Int_t n) const;
    Bool_t GetValue(TString name, Int_t &v) const {return GetValue(name, &v, 1);};
    Bool_t GetValue(TString name, Double_t &v) const {return GetValue(name, &v, 1);};
    Bool_t IsValue(TString name, TString value) const {return GetValue(name).EqualTo(value);};
    
    Bool_t RegisterDelegate(TString name, delegate_t *delegate, TClass *delegate_class);
    delegate_t *GetDelegate(TString name) const {return fDelegate.at(name);};
    const delegate_map_t &DelegateMap() const {return fDelegate;};

    
    virtual void NotifyUpdate(TString value, TString args) {};

  private:

    value_map_t fValue;
    delegate_map_t fDelegate;
    std::map<TString, TClass *> fDelegateClass;
    
    static TString fgPrependCommand;
    
    ClassDefOverride(ConfigurationManager, 1)
      
  }; /** class ConfigurationManager **/

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_CONFIGURATIONMANAGER_H_ */

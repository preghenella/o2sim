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
    virtual Bool_t Init() = 0;
    
  protected:

    /** methods **/
    virtual Bool_t ProcessCommand(TString command);
    void PrintStatus(TString prepend = "") const;

    Bool_t RegisterValue(TString name, value_t value);
    value_t GetValue(TString name) {return fValue[name];};
    Bool_t ValidValue(TString name) {return fValue.count(name) == 1;};
    Bool_t ParseValue(TString name, Float_t *ret, Int_t n);
    Bool_t ParseValue(TString name, Int_t *ret, Int_t n);

    Bool_t RegisterDelegate(TString name, delegate_t *delegate);
    delegate_t *GetDelegate(TString name) {return fDelegate[name];};
    const delegate_map_t &DelegateMap() const {return fDelegate;};

    
    virtual void NotifyUpdate(TString value, TString args) {};

  private:

    value_map_t fValue;
    delegate_map_t fDelegate;
    
    ClassDefOverride(ConfigurationManager, 1)
      
  }; /** class ConfigurationManager **/

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_CONFIGURATIONMANAGER_H_ */

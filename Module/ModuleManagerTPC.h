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

#ifndef ALICEO2SIM_MODULEMANAGERTPC_H_
#define ALICEO2SIM_MODULEMANAGERTPC_H_

#include "Core/ModuleManagerDelegate.h"

namespace o2sim {

  class ModuleManagerTPC : public ModuleManagerDelegate
  {

  public:

    /** default constructor **/
    ModuleManagerTPC();

    /** methods **/
    FairModule *Init() const override;
    Bool_t Terminate() const override {return kTRUE;}; 

  private:

    ClassDefOverride(ModuleManagerTPC, 1)
  }; /** class ModuleManagerTPC **/
  
} /** namespace o2sim **/

#endif /* ALICEO2SIM_MODULEMANAGERTPC_H_ */

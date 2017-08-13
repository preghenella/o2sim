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

#ifndef ALICEO2SIM_MODULEMANAGERDELEGATE_H_
#define ALICEO2SIM_MODULEMANAGERDELEGATE_H_

#include "Core/ConfigurationManager.h"

class FairModule;
class TString;

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class ModuleManagerDelegate : public ConfigurationManager
  {

  public:

    /** default constructor **/
    ModuleManagerDelegate();

    /** methods **/
    FairModule *GetModule() {return fModule;};

  protected:

    /** members **/
    FairModule *fModule;
    
    ClassDefOverride(ModuleManagerDelegate, 1)
      
  }; /** class ModuleManagerDelegate **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_MODULEMANAGERDELEGATE_H_ */

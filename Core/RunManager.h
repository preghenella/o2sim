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

#ifndef ALICEO2SIM_RUNMANAGER_H_
#define ALICEO2SIM_RUNMANAGER_H_

#include "ConfigurationManager.h"

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/
  
  class RunManager : public ConfigurationManager
  {

  public:

    /** default constructor **/
    RunManager();

    /** methods **/
    virtual Bool_t ProcessCommand(TString command) override;
    void PrintStatus();
    Bool_t Init() override;
    Bool_t Run();
    Bool_t ProcessFile(TString filename);
    
  private:

    ClassDefOverride(RunManager, 1)
      
  }; /** class RunManager **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_RUNMANAGER_H_ */

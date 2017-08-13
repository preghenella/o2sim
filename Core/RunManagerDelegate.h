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

#ifndef ALICEO2SIM_RUNMANAGERDELEGATE_H_
#define ALICEO2SIM_RUNMANAGERDELEGATE_H_

#include "CommandProcessor.h"

class FairRunSim;

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class RunManagerDelegate : public CommandProcessor
  {

  public:

    /** default constructor **/
    RunManagerDelegate();

    /** methods **/
    virtual Bool_t Init(FairRunSim *runsim) = 0;

  protected:

    ClassDefOverride(RunManagerDelegate, 1)
      
  }; /** class RunManagerDelegate **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_RUNMANAGERDELEGATE_H_ */

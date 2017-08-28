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

#ifndef ALICEO2SIM_TRIGGERMANAGERDELEGATE_H_
#define ALICEO2SIM_TRIGGERMANAGERDELEGATE_H_

#include "Core/ConfigurationManager.h"

namespace o2 {
namespace eventgen {
  class Trigger;
}}

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class TriggerManagerDelegate : public ConfigurationManager
  {

  public:

    /** default constructor **/
    TriggerManagerDelegate();

    /** methods **/
    virtual o2::eventgen::Trigger *Init() const = 0;
    virtual Bool_t Terminate() const = 0;

  protected:

  private:

    ClassDefOverride(TriggerManagerDelegate, 1)
      
  }; /** class TriggerManagerDelegate **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_TRIGGERMANAGERDELEGATE_H_ */

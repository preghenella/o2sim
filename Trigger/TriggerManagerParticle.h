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

#ifndef ALICEO2SIM_TRIGGERMANAGERPARTICLE_H_
#define ALICEO2SIM_TRIGGERMANAGERPARTICLE_H_

#include "TriggerManagerDelegate.h"

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class TriggerManagerParticle : public TriggerManagerDelegate
  {

  public:
    
    /** default constructor **/
    TriggerManagerParticle();

    /** methods **/
    o2::eventgen::Trigger *Init() const override;
    Bool_t Terminate() const override;
    
  private:

    ClassDefOverride(TriggerManagerParticle, 1)
      
  }; /** class TriggerManagerParticle **/

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

#endif /* ALICEO2SIM_TRIGGERMANAGERPARTICLE_H_ */

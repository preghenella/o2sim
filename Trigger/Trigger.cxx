// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "Trigger.h"
#include "FairLogger.h"
#include "TClonesArray.h"
#include "TGenerator.h"
#include "TParticle.h"
#include "TRandom.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  Trigger::Trigger() :
    TNamed("ALICEo2", "ALICEo2 Generator Trigger"),
    fDownscale(1.),
    fNumberOfTimeSlots(1),
    fActiveTimeSlot(0),
    fTimeSlot(0)
  {
    /** default contructor **/
  }

  /*****************************************************************/
  
  Trigger::~Trigger()
  {
    /** default destructor **/
  }

  /*****************************************************************/
  
  Bool_t
  Trigger::IsActive()
  {
    /** trigger event **/

    /** check active time slot **/
    if (fTimeSlot != fActiveTimeSlot) {
      fTimeSlot = (fTimeSlot + 1) % fNumberOfTimeSlots;
      return kFALSE;
    }
    fTimeSlot = (fTimeSlot + 1) % fNumberOfTimeSlots;

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /* namespace eventgen */
} /* namespace o2 */

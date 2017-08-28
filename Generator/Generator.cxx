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

#include "Generator.h"
#include "GeneratorHeader.h"
#include "FairPrimaryGenerator.h"
#include "PrimaryGenerator.h"
#include "Trigger/Trigger.h"
#include "FairLogger.h"
#include <cmath>

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  Generator::Generator() :
    FairGenerator("ALICEo2", "ALICEo2 Generator"),
    fTriggerMode(kTriggerOFF),
    fMaxTriggerAttempts(100000),
    fTriggers(new TObjArray()),
    fBoost(0.),
    fHeader(new GeneratorHeader())
  {
    /** default constructor **/

  }

  /*****************************************************************/

  Generator::Generator(const Char_t *name, const Char_t *title) :
    FairGenerator(name, title),
    fTriggerMode(kTriggerOFF),
    fMaxTriggerAttempts(100000),
    fTriggers(new TObjArray()),
    fBoost(0.),
    fHeader(new GeneratorHeader(name))
  {
    /** constructor **/

  }

  /*****************************************************************/

  Generator::~Generator()
  {
    /** default destructor **/

    if (fTriggers) delete fTriggers;
    if (fHeader) delete fHeader;
  }

  /*****************************************************************/

  void
  Generator::AddTrigger(Trigger *trigger)
  {
    /** add trigger **/

    fTriggers->Add(trigger);
  }
  
  /*****************************************************************/

  Bool_t
  Generator::ReadEvent(FairPrimaryGenerator *primGen)
  {
    /** read event **/

    /** reset header **/
    fHeader->Reset();
    
    /** trigger loop **/
    Int_t nAttempts = 0;
    do {
      
      /** check attempts **/
      nAttempts++;
      if (nAttempts % 1000 == 0)
	LOG(WARNING) << "Large number of trigger attempts: " << nAttempts << std::endl;
      else if (nAttempts > fMaxTriggerAttempts) {
	LOG(ERROR) << "Maximum number of trigger attempts exceeded: " << fMaxTriggerAttempts << std::endl;
	return kFALSE;
      }
      
      /** generate event **/
      if (!GenerateEvent()) return kFALSE;

      /** boost event **/
      if (!BoostEvent(fBoost)) return kFALSE;      

    } while (!TriggerEvent()); /** end of trigger loop **/

    /** accept event **/
    return AcceptEvent(primGen);
  }

  /*****************************************************************/

  Bool_t
  Generator::TriggerEvent() const
  {
    /** trigger event **/

    auto triggered = kTRUE;
    if (fTriggers->GetEntries() == 0) return kTRUE;
    else if (fTriggerMode == kTriggerOFF) return kTRUE;
    else if (fTriggerMode == kTriggerOR) triggered = kFALSE;
    else if (fTriggerMode == kTriggerAND) triggered = kTRUE;
    else return kTRUE;
    
    /** loop over triggers **/
    for (Int_t itrigger = 0; itrigger < fTriggers->GetEntries(); itrigger++) {
      auto trigger = dynamic_cast<Trigger *>(fTriggers->At(itrigger));
      if (!trigger) continue;
      auto retval = TriggerFired(trigger);
      if (fTriggerMode == kTriggerOR) triggered |= retval;
      if (fTriggerMode == kTriggerAND) triggered &= retval;
    } /** end of loop over triggers **/

    /** success **/
    return triggered;
  }

  /*****************************************************************/

  Bool_t
  Generator::AddHeader(PrimaryGenerator *primGen) const
  {
    /** add header **/

    primGen->AddHeader(fHeader);
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

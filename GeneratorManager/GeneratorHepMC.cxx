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

#include "GeneratorHepMC.h"
#include "TriggerManager/TriggerHepMC.h"
#include "FairLogger.h"
#include "FairPrimaryGenerator.h"
#include "HepMC/ReaderAscii.h"
#include "HepMC/ReaderAsciiHepMC2.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  GeneratorHepMC::GeneratorHepMC() :
    FairGenerator("ALICEo2", "ALICEo2 HepMC Generator"),
    fStream(),
    fFileName(),
    fVersion(3),
    fReader(NULL),
    fEvent(NULL),
    fTriggers(NULL),
    fTriggerMode(kTriggerOR)
  {
    /** default constructor **/

    fEvent = new HepMC::GenEvent();
    fTriggers = new TObjArray();
    //    fTriggers->SetOwner(kTRUE);
    
  }

  /*****************************************************************/

  GeneratorHepMC::~GeneratorHepMC()
  {
    /** default destructor **/

    if (fStream.is_open()) fStream.close();
    if (fReader) {
      fReader->close();
      delete fReader;
    }
    if (fEvent) delete fEvent;
    //    if (fTriggers) delete fTriggers;
  }

  /*****************************************************************/

  void
  GeneratorHepMC::AddTrigger(Trigger *trigger)
  {
    /** add trigger **/

    fTriggers->Add(trigger);
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorHepMC::ReadEvent(FairPrimaryGenerator *primGen)
  {
    /** read event **/

    /** check reader **/
    if (!fReader) return kFALSE;

    /** generate and trigger loop **/
    Bool_t triggered;
    Int_t nAttempts = 0;
    do {

      nAttempts++;
      if (nAttempts % 1000 == 0)
	LOG(WARNING) << "Large number of trigger attempts: " << nAttempts << std::endl;
      
      /** clear and read event **/
      fEvent->clear();
      fReader->read_event(*fEvent);
      if(fReader->failed()) return kFALSE;      
      /** set units to desired output **/
      fEvent->set_units(HepMC::Units::GEV, HepMC::Units::CM);

      /** trigger event **/
      if (fTriggers->GetEntries() == 0) break; // no trigger applied
      if (fTriggerMode == kTriggerOR) triggered = kFALSE;
      else if (fTriggerMode == kTriggerAND) triggered = kTRUE;
      else break; // unkown trigger mode
      /** loop over triggers **/
      for (Int_t itrigger = 0; itrigger < fTriggers->GetEntries(); itrigger++) {
	auto trigger = dynamic_cast<TriggerHepMC *>(fTriggers->At(itrigger));
	if (!trigger) {
	  LOG(ERROR) << "Incompatile trigger for HepMC interface" << std::endl;
	  return kFALSE;
	}
	Bool_t retval = trigger->TriggerEvent(fEvent);
	if (fTriggerMode == kTriggerOR) triggered |= retval;
	if (fTriggerMode == kTriggerAND) triggered &= retval;
      } /** and of loop over triggers **/
      
    } while (!triggered); /** end of generate and trigger loop **/

    /** add particles **/
    
    /** loop over particles **/
    auto particles = fEvent->particles();
    for (auto const &particle : particles) {
      
      /** get particle information **/
      auto pdg = particle->pid();
      auto st = particle->status();
      auto momentum = particle->momentum();
      auto vertex = particle->production_vertex()->position();
      auto parents = particle->parents(); // less efficient than via vertex
      auto children = particle->children(); // less efficient than via vertex
      
      /** get momentum information **/
      auto px = momentum.x();
      auto py = momentum.y();
      auto pz = momentum.z();
      auto et = momentum.t();
      
      /** get vertex information **/
      auto vx = vertex.x();
      auto vy = vertex.y();
      auto vz = vertex.z();
      auto vt = vertex.t();
      
      /** get mother information **/
      auto mm = parents.empty() ? -1 : parents.back()->id() - 1; // not obvious why reversed
      
      /** get weight information [WIP] **/
      auto ww = 1.;
      
      /** set want tracking [WIP] **/
      auto wt = (st == 1 || children.empty());
      
      /* add track */
      primGen->AddTrack(pdg, px, py, pz, vx, vy, vz, mm, wt, et, vt, ww);
      
    } /** end of loop over particles **/
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorHepMC::Init()
  {
    /*
     * init
     */

    /** open file **/
    fStream.open(fFileName);
    if (!fStream.is_open()) {
      LOG(ERROR) << "Cannot open input file: " << fFileName << std::endl;
      return kFALSE;
    }
    
    /** create reader according to HepMC version **/
    switch (fVersion) {
    case 2:
      fStream.close();
      fReader = new HepMC::ReaderAsciiHepMC2(fFileName);
      break;
    case 3:
      fReader = new HepMC::ReaderAscii(fStream);
      break;
    default:
      LOG(ERROR) << "Unsupported HepMC version: " << fVersion << std::endl;
      return kFALSE;
    }
      
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

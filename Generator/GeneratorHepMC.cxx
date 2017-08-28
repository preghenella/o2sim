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
#include "Trigger/TriggerHepMC.h"
#include "FairLogger.h"
#include "FairPrimaryGenerator.h"
#include "HepMC/ReaderAscii.h"
#include "HepMC/ReaderAsciiHepMC2.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "HepMC/FourVector.h"
#include <cmath>

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
    fTriggerMode(kTriggerOR),
    fBoost(0.),
    fMaxAttempts(100000)
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

    /** trigger loop **/
    Int_t nAttempts = 0;
    do {
      
      /** check attempts **/
      if (nAttempts % 1000 == 0)
	LOG(WARNING) << "Large number of trigger attempts: " << nAttempts << std::endl;
      else if (nAttempts > fMaxAttempts) {
	LOG(ERROR) << "Maximum number of trigger attempts exceeded: " << fMaxAttempts << std::endl;
	return kFALSE;
      }
      
      /** generate event **/
      if (!GenerateEvent(fEvent)) return kFALSE;
      nAttempts++;

      /** boost event **/
      BoostEvent(fEvent, fBoost);      

    } while (!TriggerEvent(fEvent)); /** end of trigger loop **/

    /** accept event **/
    return AcceptEvent(fEvent, primGen);
  }

  /*****************************************************************/

  Bool_t
  GeneratorHepMC::GenerateEvent(HepMC::GenEvent *event)
  {
    /** generate event **/

    /** clear and read event **/
    event->clear();
    fReader->read_event(*event);
    if(fReader->failed()) return kFALSE;      
    /** set units to desired output **/
    fEvent->set_units(HepMC::Units::GEV, HepMC::Units::CM);

    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorHepMC::TriggerEvent(HepMC::GenEvent *event)
  {
    /** trigger event **/
    
    Bool_t triggered;
    if (fTriggers->GetEntries() == 0) return kTRUE;
    else if (fTriggerMode == kTriggerOFF) return kTRUE;
    else if (fTriggerMode == kTriggerOR) triggered = kFALSE;
    else if (fTriggerMode == kTriggerAND) triggered = kTRUE;
    else return kTRUE;
    
    /** loop over triggers **/
    for (Int_t itrigger = 0; itrigger < fTriggers->GetEntries(); itrigger++) {
      auto trigger = dynamic_cast<TriggerHepMC *>(fTriggers->At(itrigger));
      if (!trigger) {
	LOG(ERROR) << "Incompatile trigger for HepMC interface" << std::endl;
	return kFALSE;
      }
      Bool_t retval = trigger->TriggerEvent(event);
      if (fTriggerMode == kTriggerOR) triggered |= retval;
      if (fTriggerMode == kTriggerAND) triggered &= retval;
    } /** end of loop over triggers **/

    /** success **/
    return triggered;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorHepMC::AcceptEvent(HepMC::GenEvent *event, FairPrimaryGenerator *primGen)
  {
    /** accept event **/
    
    /** loop over particles **/
    auto particles = event->particles();
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
      auto vt = vertex.t() * 3.33564095198152022e-11; // [cm -> s]
      
      /** get mother information **/
      auto mm = parents.empty() ? -1 : parents.front()->id() - 1;
      
      /** get weight information [WIP] **/
      auto ww = 1.;
      
      /** set want tracking [WIP] **/
      auto wt = children.empty();

      /* add track */
      primGen->AddTrack(pdg, px, py, pz, vx, vy, vz, mm, wt, et, vt, ww);
      
    } /** end of loop over particles **/
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  void
  GeneratorHepMC::BoostEvent(HepMC::GenEvent *event, Double_t boost)
  {
    /** boost **/

    /** loop over particles **/
    if (std::abs(boost) < 1.e-6) return;
    auto particles = event->particles();
    for (auto &particle : particles) {
      auto momentum = GetBoostedVector(particle->momentum(), boost);
      particle->set_momentum(momentum);
      auto position = GetBoostedVector(particle->production_vertex()->position(), boost);
      particle->production_vertex()->set_position(position);
    }
    
  }
  
  /*****************************************************************/

  const HepMC::FourVector
  GeneratorHepMC::GetBoostedVector(const HepMC::FourVector &vector, Double_t boost)
  {
    /** boost **/

    auto x = vector.x();
    auto y = vector.y();
    auto z = vector.z();
    auto t = vector.t();
    auto coshb = std::cosh(boost);
    auto sinhb = std::sinh(boost);
    auto xx = x;
    auto yy = y;
    auto zz = z * coshb - t * sinhb;
    auto tt = t * coshb - z * sinhb;
    return HepMC::FourVector(xx, yy, zz, tt);
  }

  /*****************************************************************/

  Bool_t
  GeneratorHepMC::Init()
  {
    /** init **/

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

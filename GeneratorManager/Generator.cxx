// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "Generator.h"
#include "TriggerManager/TriggerTGenerator.h"
#include "FairLogger.h"
#include "FairPrimaryGenerator.h"
#include "TGenerator.h"
#include "TClonesArray.h"
#include "TParticle.h"

namespace o2
{
namespace eventgen
{

  Generator::Generator() :
    FairGenerator("ALICEo2", "ALICEo2 Event Generator"),
    fGenerator(NULL),
    fTriggers(NULL),
    fParticles(NULL),
    fTriggerMode(kTriggerOR),
    fNumberOfEvents(1)
  {
    /*
     * default constructor
     */

    /** array of triggers **/ 
    fTriggers = new TObjArray();

    /** array of generated particles **/ 
    fParticles = new TClonesArray("TParticle");
    fParticles->SetOwner(kTRUE);

  }

  Generator::Generator(const Char_t *name, const Char_t *title) :
    FairGenerator(name, title),
    fGenerator(NULL),
    fTriggers(NULL),
    fTriggerMode(kTriggerOR),
    fParticles(NULL)
  {
    /*
     * contructor with name and title
     */

    /** array of triggers **/ 
    fTriggers = new TObjArray();

    /** array of generated particles **/ 
    fParticles = new TClonesArray("TParticle");
    fParticles->SetOwner(kTRUE);

  }

  void
  Generator::AddTrigger(Trigger *val)
  {
    /** add trigger **/
    fTriggers->Add(val);
  }

  Bool_t
  Generator::ReadEvent(FairPrimaryGenerator *primGen)
  {
    /*
     * read event
     */

    /** loop over number of events **/
    for (Int_t iev = 0; iev < fNumberOfEvents; iev++) {
      
      /** generate and trigger event **/
      Bool_t triggered = fTriggers->GetEntries() == 0;
      Int_t nAttempts = 0;
      do {
	
	nAttempts++;
	if (nAttempts % 1000 == 0)
	  LOG(WARNING) << "Large number of trigger attempts: " << nAttempts << std::endl;
	
	/** generate event **/
	fGenerator->GenerateEvent();
	fGenerator->ImportParticles(fParticles, "All");
	
	/** trigger event **/
	if (fTriggerMode == kTriggerOR) triggered = kFALSE;
	if (fTriggerMode == kTriggerAND) triggered = kTRUE;
	if (fTriggers->GetEntries() == 0) triggered = kTRUE;
	for (Int_t itrigger = 0; itrigger < fTriggers->GetEntries(); itrigger++) {
	  auto trigger = dynamic_cast<TriggerTGenerator *>(fTriggers->At(itrigger));
	  if (!trigger) {
	    LOG(ERROR) << "Incompatile trigger for TGenerator interface" << std::endl;
	    return kFALSE;
	  }
	  Bool_t retval = trigger->TriggerEvent(fParticles, fGenerator);
	  if (fTriggerMode == kTriggerOR) triggered |= retval;
	  if (fTriggerMode == kTriggerAND) triggered &= retval;
	}
	
      } while (!triggered);
	
      /* add tracks */
      Int_t nParticles = fParticles->GetEntries();
      TParticle *particle = NULL;
      for (Int_t iparticle = 0; iparticle < nParticles; iparticle++) {
	particle = (TParticle *)fParticles->At(iparticle);
	if (!particle) continue;
	primGen->AddTrack(particle->GetPdgCode(),
			  particle->Px(), particle->Py(), particle->Pz(),
			  particle->Vx(), particle->Vy(), particle->Vz(),
			  particle->GetMother(0),
			  particle->GetStatusCode() == 1,
			  particle->Energy(),
			  particle->T(),
			  particle->GetWeight());
      }
    }
    
    /** success **/
    return kTRUE;
  }

  Bool_t
  Generator::Init()
  {
    /*
     * init
     */

    /** success **/
    return kTRUE;
  }

} /* namespace eventgen */
} /* namespace o2 */

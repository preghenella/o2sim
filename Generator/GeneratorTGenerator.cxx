// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "GeneratorTGenerator.h"
#include "Trigger/TriggerTGenerator.h"
#include "FairLogger.h"
#include "FairPrimaryGenerator.h"
#include "TGenerator.h"
#include "TClonesArray.h"
#include "TParticle.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  GeneratorTGenerator::GeneratorTGenerator() :
    Generator("ALICEo2", "ALICEo2 TGenerator Generator"),
    fGenerator(NULL),
    fParticles(NULL)
  {
    /** default constructor **/

  }

  /*****************************************************************/

  GeneratorTGenerator::GeneratorTGenerator(const Char_t *name, const Char_t *title) :
    Generator(name, title),
    fGenerator(NULL),
    fParticles(NULL)
  {
    /** constructor **/

  }

  /*****************************************************************/

  GeneratorTGenerator::~GeneratorTGenerator()
  {
    /** default destructor **/

    if (fParticles) delete fParticles;
  }

  /*****************************************************************/

  Bool_t
  GeneratorTGenerator::GenerateEvent()
  {
    /** generate event **/

    fGenerator->GenerateEvent();
    fGenerator->ImportParticles(fParticles, "All");

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorTGenerator::BoostEvent(Double_t boost)
  {
    /** boost event **/

    LOG(WARNING) << "Boost not implemented yet" << std::endl;
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorTGenerator::TriggerFired(Trigger *trigger) const
  {
    /** trigger event **/

    auto aTrigger = dynamic_cast<TriggerTGenerator *>(trigger);
    if (!aTrigger) {
      LOG(ERROR) << "Incompatile trigger for HepMC interface" << std::endl;
      return kFALSE;
    }    
    return aTrigger->TriggerEvent(fParticles, fGenerator);

  }

  /*****************************************************************/
  
  Bool_t
  GeneratorTGenerator::AcceptEvent(FairPrimaryGenerator *primGen) const
  {
    /** accept event **/
    
    /* loop over particles */
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
    
    /** success **/
    return kTRUE;
  }

  /*****************************************************************/

  Bool_t
  GeneratorTGenerator::Init()
  {
    /** init **/

    if (!fGenerator) {
      LOG(ERROR) << "No TGenerator inteface assigned" << std::endl;
      return kFALSE;
    }
    
    /** array of generated particles **/ 
    fParticles = new TClonesArray("TParticle");
    fParticles->SetOwner(kTRUE);

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /* namespace eventgen */
} /* namespace o2 */

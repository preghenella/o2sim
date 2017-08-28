// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "ParticleTrigger.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "TClonesArray.h"
#include "TParticle.h"
#include <cmath>

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  ParticleTrigger::ParticleTrigger() :
    Trigger(),
    TriggerHepMC(),
    TriggerTGenerator(),
    fPdgCode(0),
    fPtMin(0.),
    fPtMax(1.e9),
    fYMin(-1.e9),
    fYMax(1.e9)
  {
    /** default contructor */
  }

  /*****************************************************************/

  ParticleTrigger::~ParticleTrigger()
  {
    /** default destructor **/
  }

  /*****************************************************************/

  Bool_t
  ParticleTrigger::IsTriggered(HepMC::GenEvent *event) const
  {
    /** is triggered **/

    /** loop over particles **/
    for (auto const &particle : event->particles()) {

      /** get momentum information **/
      auto pdg = particle->pid();      
      auto momentum = particle->momentum();
      auto px = momentum.x();
      auto py = momentum.y();
      auto pz = momentum.z();
      auto et = momentum.t();
      auto pt = sqrt(px * px + py * py);
      auto pp = sqrt(px * px + py * py + pz * pz);
      auto rapidity = 0.5 * log ( (et + pz) / (et - pz) );

      /** check pdg **/
      if (pdg != fPdgCode) continue;
      /** check pt **/
      if (pt < fPtMin) continue;
      if (pt > fPtMax) continue;
      /** check rapidity **/
      if (rapidity < fYMin) continue;
      if (rapidity > fYMax) continue;

      /** success **/
      return kTRUE;
    }

    /** failure **/
    return kFALSE;
  }
  
  /*****************************************************************/
  
  Bool_t
  ParticleTrigger::IsTriggered(TClonesArray *particles, TGenerator *generator) const
  {
    /** is triggered **/

    /* add tracks */
    Int_t nParticles = particles->GetEntries();
    TParticle *particle = NULL;
    for (Int_t iparticle = 0; iparticle < nParticles; iparticle++) {
      particle = (TParticle *)particles->At(iparticle);
      if (!particle) continue;
      if (particle->GetPdgCode() != fPdgCode) continue;
      if (particle->Pt() < fPtMin) continue;
      if (particle->Pt() > fPtMax) continue;
      if (particle->Y() < fYMin) continue;
      if (particle->Y() > fYMax) continue;
      return kTRUE;
    }

    return kFALSE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace eventgen **/
} /** namespace o2 **/

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

#include "TriggerManagerParticle.h"
#include "ParticleTrigger.h"

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  TriggerManagerParticle::TriggerManagerParticle() :
    TriggerManagerDelegate()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("pdg_code");
    RegisterValue("pt");
    RegisterValue("rapidity");
  }

  /*****************************************************************/

  o2::eventgen::Trigger *
  TriggerManagerParticle::Init() const
  {
    /** init **/

    Int_t pdg_code;
    Double_t pt[2], rapidity[2];

    /** pdg code **/
    if (!GetValue("pdg_code", pdg_code) || pdg_code == 0) {
      LOG(ERROR) << "Invalid PDG code" << std::endl;
      return NULL;
    }

    /** create trigger **/ 
    o2::eventgen::ParticleTrigger *trigger = new o2::eventgen::ParticleTrigger();
    trigger->SetPdgCode(pdg_code);

    /** setup trigger **/

    /** pt **/
    if (!IsNull("pt")) {
      if (!GetValue("pt", pt, 2) || pt[0] > pt[1]) {
	LOG(ERROR) << "Invalid pt range" << std::endl;
	return NULL;
      }
      trigger->SetPtRange(pt[0], pt[1]);
    }
    /** rapidity **/
    if (!IsNull("rapidity")) {
      if (!GetValue("rapidity", rapidity, 2) || rapidity[0] > rapidity[1]) {
	LOG(ERROR) << "Invalid rapidity range" << std::endl;
	return NULL;
      }
      trigger->SetYRange(rapidity[0], rapidity[1]);
    }

    /** success **/
    return trigger;
  }
  
  /*****************************************************************/

  Bool_t
  TriggerManagerParticle::Terminate() const
  {
    /** terminate **/

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

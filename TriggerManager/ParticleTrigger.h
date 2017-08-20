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

#ifndef ALICEO2_EVENTGEN_PARTICLETRIGGER_H_
#define ALICEO2_EVENTGEN_PARTICLETRIGGER_H_

#include "TriggerHepMC.h"
#include "TriggerTGenerator.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  class ParticleTrigger : public TriggerHepMC, public TriggerTGenerator
  {
    
  public:
    
    /** default constructor **/
    ParticleTrigger();
    /** destructor **/
    virtual ~ParticleTrigger();

    void SetPdgCode(Int_t val) {fPdgCode = val;};
    void SetPtRange(Double_t min, Double_t max) {fPtMin = min; fPtMax = max;};
    void SetPtMin(Double_t val) {fPtMin = val;};
    void SetPtMax(Double_t val) {fPtMax = val;};
    void SetYRange(Double_t min, Double_t max) {fYMin = min; fYMax = max;};
    void SetYMin(Double_t val) {fYMin = val;};
    void SetYMax(Double_t val) {fYMax = val;};

  protected:

    /** copy constructor **/
    ParticleTrigger(const ParticleTrigger &);
    /** operator= **/
    ParticleTrigger &operator=(const ParticleTrigger &);
    
    virtual Bool_t IsTriggered(HepMC::GenEvent *event) const override;
    virtual Bool_t IsTriggered(TClonesArray *particles, TGenerator *generator) const override;

    Int_t fPdgCode;
    Double_t fPtMin;
    Double_t fPtMax;
    Double_t fYMin;
    Double_t fYMax;
    
    ClassDefOverride(ParticleTrigger, 1);

  }; /** class ParticleTrigger **/
  }

/*****************************************************************/
  /*****************************************************************/

 /** namespace eventgen **/
} /** namespace o2 **/

#endif /** ALICEO2_EVENTGEN_PARTICLETRIGGER_H_ **/ 

// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \author R+Preghenella - June 2017

#ifndef ALICEO2_EVENTGEN_TRIGGER_H_
#define ALICEO2_EVENTGEN_TRIGGER_H_

#include "TNamed.h"
#include "TRandom.h"

namespace HepMC {
  class GenEvent;
}

class TClonesArray;
class TGenerator;

namespace o2
{
namespace eventgen
{

  class Trigger : public TNamed
  {
    
  public:
    
    /** default constructor **/
    Trigger();
    /** constructor with name and title **/
    Trigger(const Char_t *name, const Char_t *title = "ALICEo2 Generator Trigger");
    /** destructor **/
    //      virtual ~Trigger();

    /** getters **/
    Double_t GetDownscale() const {return fDownscale;};
    UInt_t GetNumberOfTimeSlots() const {return fNumberOfTimeSlots;};
    UInt_t GetActiveTimeSlot() const {return fActiveTimeSlot;};

    /** setters **/
    void SetDownscale(Double_t val) {fDownscale = val;};
    void SetNumberOfTimeSlots(UInt_t val) {fNumberOfTimeSlots = val;};
    void SetActiveTimeSlot(UInt_t val) {fActiveTimeSlot = val;};

    /** methods **/
    Bool_t TriggerEvent(TClonesArray *particles, TGenerator *generator);
    Bool_t TriggerEvent(HepMC::GenEvent *event);
        
  protected:
    
    /** copy constructor **/
    Trigger(const Trigger &);
    /** operator= **/
    Trigger &operator=(const Trigger &);

    /** methods **/
    virtual Bool_t IsTriggered(TClonesArray *particles, TGenerator *generator) const = 0;
    virtual Bool_t IsTriggered(HepMC::GenEvent *event) const = 0;

    /** methods **/
    Bool_t IsActive();
    Bool_t IsDownscaled() {return gRandom->Uniform() > fDownscale;};

    /** data members **/
    Double_t fDownscale;
    UInt_t fNumberOfTimeSlots;
    UInt_t fActiveTimeSlot;
        
  private:

    UInt_t fTimeSlot;

    ClassDefOverride(Trigger, 1);
  };
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_TRIGGER_H_ */ 

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

#ifndef ALICEO2_EVENTGEN_TRIGGERHEPMC_H_
#define ALICEO2_EVENTGEN_TRIGGERHEPMC_H_

#include "Trigger.h"

namespace HepMC {
  class GenEvent;
}

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  class TriggerHepMC : public virtual Trigger
  {
    
  public:
    
    /** default constructor **/
    TriggerHepMC();
    /** destructor **/
    virtual ~TriggerHepMC();

    /** methods **/
    Bool_t TriggerEvent(HepMC::GenEvent *event);
    
  protected:
    
    /** copy constructor **/
    TriggerHepMC(const TriggerHepMC &);
    /** operator= **/
    TriggerHepMC &operator=(const TriggerHepMC &);

  private:

    /** methods **/
    virtual Bool_t IsTriggered(HepMC::GenEvent *event) const = 0;
    
    ClassDefOverride(TriggerHepMC, 1);

  }; /** class TriggerHepMC **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace eventgen **/
} /** namespace o2 **/

#endif /* ALICEO2_EVENTGEN_TRIGGERHEPMC_H_ */ 

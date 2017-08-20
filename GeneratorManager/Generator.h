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

#ifndef ALICEO2_EVENTGEN_GENERATOR_H_
#define ALICEO2_EVENTGEN_GENERATOR_H_

#include "FairGenerator.h"

class TGenerator;
class TClonesArray;
class TObjArray;

namespace o2
{
namespace eventgen
{

  class Trigger;
  
  class Generator : public FairGenerator
  {
    
  public:

    enum ETriggerMode_t {
      kTriggerOR,
      kTriggerAND
    };
    
    /** default constructor **/
    Generator();
    /** constructor with name and title **/
    Generator(const Char_t *name, const Char_t *title = "ALICEo2 Event Generator");
    /** destructor **/
    //      virtual ~Generator();

    /** setters **/
    void SetGenerator(TGenerator *val) {fGenerator = val;};
    void AddTrigger(Trigger *val);

    /** Abstract method ReadEvent must be implemented by any derived class.
	It has to handle the generation of input tracks (reading from input
	file) and the handing of the tracks to the FairPrimaryGenerator. I
	t is called from FairMCApplication.
	*@param pStack The stack
	*@return kTRUE if successful, kFALSE if not
	**/
    virtual Bool_t ReadEvent(FairPrimaryGenerator *primGen) override;
    
    /** Initialize the generator if needed **/
    virtual Bool_t Init() override;

    /** setters **/
    void SetTriggerMode(ETriggerMode_t val) {fTriggerMode = val;};
    void SetNumberOfEvents(Int_t val) {fNumberOfEvents = val;};
    
  protected:
    /** copy constructor **/
    Generator(const Generator &);
    /** operator= **/
    Generator &operator=(const Generator &);

    /** plugin interfaces **/
    TGenerator *fGenerator;
    TObjArray *fTriggers;
    
    /** generator data **/
    TClonesArray *fParticles;

    /** data members **/
    ETriggerMode_t fTriggerMode;
    Int_t fNumberOfEvents;
    
    ClassDefOverride(Generator, 1);
  };
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_GENERATOR_H_ */ 

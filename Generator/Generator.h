
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

#ifndef ALICEO2_EVENTGEN_GENERATOR_H_
#define ALICEO2_EVENTGEN_GENERATOR_H_

#include "FairGenerator.h"

namespace o2
{
namespace eventgen
{

  class PrimaryGenerator;
  class GeneratorHeader;
  class Trigger;
  
  /*****************************************************************/
  /*****************************************************************/
    
  class Generator : public FairGenerator
  {
    
  public:

    enum ETriggerMode_t {
      kTriggerOFF,
      kTriggerOR,
      kTriggerAND
    };
    
    /** default constructor **/
    Generator();
    /** constructor **/
    Generator(const Char_t *name, const Char_t *title = "ALICEo2 Generator");
    /** destructor **/
    virtual ~Generator();

    /** Abstract method ReadEvent must be implemented by any derived class.
	It has to handle the generation of input tracks (reading from input
	file) and the handing of the tracks to the FairPrimaryGenerator. I
	t is called from FairMCApplication.
	*@param pStack The stack
	*@return kTRUE if successful, kFALSE if not
	**/
    Bool_t ReadEvent(FairPrimaryGenerator *primGen) override;

    /** getters **/
    GeneratorHeader *GetHeader() const {return fHeader;};
    
    /** setters **/
    void SetTriggerMode(ETriggerMode_t val) {fTriggerMode = val;};
    void SetMaxTriggerAttempts(Int_t val) {fMaxTriggerAttempts = val;};
    void AddTrigger(Trigger *trigger);
    void SetBoost(Double_t val) {fBoost = val;};

  protected:

    /** copy constructor **/
    Generator(const Generator &);
    /** operator= **/
    Generator &operator=(const Generator &);

    /** methods to override **/
    virtual Bool_t GenerateEvent() = 0;
    virtual Bool_t BoostEvent(Double_t boost) = 0;
    virtual Bool_t TriggerFired(Trigger *trigger) const = 0;
    virtual Bool_t AcceptEvent(FairPrimaryGenerator *primGen) const = 0;

    /** methods **/
    virtual Bool_t AddHeader(PrimaryGenerator *primGen) const;
    Bool_t TriggerEvent() const;
    
    /** data members **/
    ETriggerMode_t fTriggerMode;
    Int_t fMaxTriggerAttempts;
    TObjArray *fTriggers;
    Double_t fBoost;
    GeneratorHeader *fHeader;
    
    ClassDefOverride(Generator, 1);
    
  }; /** class Generator **/

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace eventgen **/
} /** namespace o2 **/

#endif /* ALICEO2_EVENTGEN_GENERATOR_H_ */ 

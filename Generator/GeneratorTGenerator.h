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

#ifndef ALICEO2_EVENTGEN_GENERATORTGENERATOR_H_
#define ALICEO2_EVENTGEN_GENERATORTGENERATOR_H_

#include "Generator.h"

class TGenerator;
class TClonesArray;

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  class GeneratorTGenerator : public Generator
  {
    
  public:

    /** default constructor **/
    GeneratorTGenerator();
    /** constructor with name and title **/
    GeneratorTGenerator(const Char_t *name, const Char_t *title = "ALICEo2 TGenerator Generator");
    /** destructor **/
    virtual ~GeneratorTGenerator();

    /** setters **/
    void SetGenerator(TGenerator *val) {fGenerator = val;};

    /** Initialize the generator if needed **/
    virtual Bool_t Init() override;

    /** setters **/
    void SetTriggerMode(ETriggerMode_t val) {fTriggerMode = val;};
    
  protected:
    /** copy constructor **/
    GeneratorTGenerator(const GeneratorTGenerator &);
    /** operator= **/
    GeneratorTGenerator &operator=(const GeneratorTGenerator &);

    /** methods to override **/
    Bool_t GenerateEvent() override;
    Bool_t BoostEvent(Double_t boost) override;
    Bool_t TriggerFired(Trigger *trigger) const override;
    Bool_t AddTracks(FairPrimaryGenerator *primGen) const override;
    
    /** TGenerator interface **/
    TGenerator *fGenerator;
    TClonesArray *fParticles;

    ClassDefOverride(GeneratorTGenerator, 1);
    
  }; /** class GeneratorTGenerator **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace eventgen **/
} /** namespace o2 **/

#endif /* ALICEO2_EVENTGEN_GENERATORTGENERATOR_H_ */ 

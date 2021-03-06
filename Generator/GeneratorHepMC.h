
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

#ifndef ALICEO2_EVENTGEN_GENERATORHEPMC_H_
#define ALICEO2_EVENTGEN_GENERATORHEPMC_H_

#include "Generator.h"
#include <fstream>

namespace HepMC {
  class Reader;
  class GenEvent;
  class FourVector;
}

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/
    
  class GeneratorHepMC : public Generator
  {
    
  public:

    /** default constructor **/
    GeneratorHepMC();
    /** constructor **/
    GeneratorHepMC(const Char_t *name, const Char_t *title = "ALICEo2 HepMC Generator");
    /** destructor **/
    virtual ~GeneratorHepMC();

    /** Initialize the generator if needed **/
    virtual Bool_t Init() override;

    /** setters **/
    void SetVersion(Int_t val) {fVersion = val;};
    void SetFileName(std::string val) {fFileName = val;};

  protected:

    /** copy constructor **/
    GeneratorHepMC(const GeneratorHepMC &);
    /** operator= **/
    GeneratorHepMC &operator=(const GeneratorHepMC &);

    /** methods to override **/
    Bool_t GenerateEvent() override;
    Bool_t BoostEvent(Double_t boost) override;
    Bool_t TriggerFired(Trigger *trigger) const override;
    Bool_t AddTracks(FairPrimaryGenerator *primGen) const override;
    
    /** methods **/
    Bool_t AddHeader(PrimaryGenerator *primGen) const override;
    const HepMC::FourVector GetBoostedVector(const HepMC::FourVector &vector, Double_t boost);

    /** HepMC interface **/
    std::ifstream fStream;
    std::string fFileName;
    Int_t fVersion;
    HepMC::Reader *fReader;
    HepMC::GenEvent *fEvent;
    
    ClassDefOverride(GeneratorHepMC, 1);
    
  }; /** class GeneratorHepMC **/
  
  /*****************************************************************/
  /*****************************************************************/
    
} /** namespace eventgen **/
} /** namespace o2 **/

#endif /* ALICEO2_EVENTGEN_GENERATORHEPMC_H_ */ 

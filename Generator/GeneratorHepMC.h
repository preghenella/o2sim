
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

#include "FairGenerator.h"
#include <fstream>

namespace HepMC {
  class GenEvent;
  class Reader;
}

namespace o2
{
namespace eventgen
{

  class Trigger;
  
  class GeneratorHepMC : public FairGenerator
  {
    
  public:

    enum ETriggerMode_t {
      kTriggerOR,
      kTriggerAND
    };
    
    /** default constructor **/
    GeneratorHepMC();
    /** destructor **/
    virtual ~GeneratorHepMC();

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
    void SetVersion(Int_t val) {fVersion = val;};
    void SetFileName(std::string val) {fFileName = val;};
    void SetTriggerMode(ETriggerMode_t val) {fTriggerMode = val;};
    void AddTrigger(Trigger *trigger);
    
  protected:

    /** copy constructor **/
    GeneratorHepMC(const GeneratorHepMC &);
    /** operator= **/
    GeneratorHepMC &operator=(const GeneratorHepMC &);

    std::ifstream fStream;
    std::string fFileName;
    Int_t fVersion;
    HepMC::Reader *fReader;
    HepMC::GenEvent *fEvent;
    TObjArray *fTriggers;

    ETriggerMode_t fTriggerMode;
    
    ClassDefOverride(GeneratorHepMC, 1);
  };
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_GENERATORHEPMC_H_ */ 

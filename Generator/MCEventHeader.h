
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

#ifndef ALICEO2_EVENTGEN_MCEVENTHEADER_H_
#define ALICEO2_EVENTGEN_MCEVENTHEADER_H_

#include "FairMCEventHeader.h"
#include <vector>

namespace o2
{
namespace eventgen
{

  class GeneratorHeader;

  /*****************************************************************/
  /*****************************************************************/
  
  class MCEventHeader : public FairMCEventHeader
  {
    
  public:

    /** default constructor **/
    MCEventHeader();
    /** copy constructor **/
    MCEventHeader(const MCEventHeader &rhs);
    /** operator= **/
    MCEventHeader &operator=(const MCEventHeader &rhs);
    /** destructor **/
    virtual ~MCEventHeader();

    /** getters **/
    const std::vector<GeneratorHeader *> &GeneratorHeaders() const {return fGeneratorHeaders;};

    /** setters **/
    void SetEmbeddingFileName(TString value) {fEmbeddingFileName = value;};
    void SetEmbeddingEventCounter(Int_t value) {fEmbeddingEventCounter = value;};
    
    /** methods **/
    virtual void Print(Option_t *opt = "") const override;
    virtual void Reset();
    virtual void AddHeader(GeneratorHeader *header);
    
  protected:

    std::vector<GeneratorHeader *> fGeneratorHeaders;
    TString fEmbeddingFileName;
    Int_t   fEmbeddingEventCounter;
    
    ClassDefOverride(MCEventHeader, 1);

  }; /** class MCEventHeader **/
  
  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_MCEVENTHEADER_H_ */ 

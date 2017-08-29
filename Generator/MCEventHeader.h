
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
#include "TClonesArray.h"

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
    Int_t GetNumberOfGeneratorHeaders() const {return fGeneratorHeaders->GetEntries();};
    GeneratorHeader *GetGeneratorHeader(Int_t igen) const {return (GeneratorHeader *)fGeneratorHeaders->At(igen);};
    
    /** methods **/
    virtual void Print(Option_t *opt = "") const override;
    virtual void Reset();
    virtual void AddHeader(GeneratorHeader *header);
    
  protected:

    TClonesArray *fGeneratorHeaders;
    
    ClassDefOverride(MCEventHeader, 1);

  }; /** class MCEventHeader **/
  
  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_MCEVENTHEADER_H_ */ 


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

#ifndef ALICEO2_EVENTGEN_GENERATORHEADER_H_
#define ALICEO2_EVENTGEN_GENERATORHEADER_H_

#include "TNamed.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/
  
  class GeneratorHeader : public TNamed
  {
    
  public:

    /** default constructor **/
    GeneratorHeader(const TString &name, const TString &title = "Generator Header");
    /** destructor **/
    virtual ~GeneratorHeader();

    /** setters **/
    void SetOffset(Int_t val) {fOffset = val;};
    void SetNTracks(Int_t val) {fNTracks = val;};
    
  protected:

    /** copy constructor **/
    GeneratorHeader(const GeneratorHeader &);
    /** operator= **/
    GeneratorHeader &operator=(const GeneratorHeader &);

    /** data **/
    Int_t fOffset;
    Int_t fNTracks;
    
    ClassDefOverride(GeneratorHeader, 1);

  }; /** class GeneratorHeader **/
  
  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_GENERATORHEADER_H_ */ 

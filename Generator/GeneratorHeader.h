
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
    GeneratorHeader();
    /** constructor **/
    GeneratorHeader(const Char_t *name, const Char_t *title = "ALICEo2 Generator Header");
    /** copy constructor **/
    GeneratorHeader(const GeneratorHeader &rhs);
    /** operator= **/
    GeneratorHeader &operator=(const GeneratorHeader &rhs);
    /** destructor **/
    virtual ~GeneratorHeader();

    /** setters **/
    void SetTrackOffset(Int_t val) {fTrackOffset = val;};
    void SetNumberOfTracks(Int_t val) {fNumberOfTracks = val;};
    void SetNumberOfAttempts(Int_t val) {fNumberOfAttempts = val;};

    /** methods **/
    virtual void Reset();
    
  protected:

    /** data **/
    Int_t fTrackOffset;
    Int_t fNumberOfTracks;
    Int_t fNumberOfAttempts;
    
    ClassDefOverride(GeneratorHeader, 1);

  }; /** class GeneratorHeader **/
  
  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_GENERATORHEADER_H_ */ 

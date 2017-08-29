
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
#include <map>

namespace o2
{
namespace eventgen
{

  class GeneratorHeaderInfo;
  class CrossSectionInfo;
  
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

    /** getters **/
    Int_t GetTrackOffset() const {return fTrackOffset;};
    Int_t GetNumberOfTracks() const {return fNumberOfTracks;};
    Int_t GetNumberOfAttempts() const {return fNumberOfAttempts;};
    CrossSectionInfo *GetCrossSectionInfo() const;
    
    /** setters **/
    void SetTrackOffset(Int_t val) {fTrackOffset = val;};
    void SetNumberOfTracks(Int_t val) {fNumberOfTracks = val;};
    void SetNumberOfAttempts(Int_t val) {fNumberOfAttempts = val;};
    
    /** methods **/
    void Print(Option_t *opt = "") const override;
    virtual void Reset();
    CrossSectionInfo *AddCrossSectionInfo();
    void RemoveCrossSectionInfo();
    
  protected:

    /** data members **/
    Int_t fTrackOffset;
    Int_t fNumberOfTracks;
    Int_t fNumberOfAttempts;
    std::map<std::string, GeneratorHeaderInfo *> fInfo;
    
    ClassDefOverride(GeneratorHeader, 1);

  }; /** class GeneratorHeader **/
  
  /*****************************************************************/
  /*****************************************************************/

  class GeneratorHeaderInfo : public TObject
  {
    
  public:

    /** default constructor **/
  GeneratorHeaderInfo() : TObject() {};
    /** copy constructor **/
  GeneratorHeaderInfo(const GeneratorHeaderInfo &rhs) : TObject(rhs) {};
    /** operator= **/
    GeneratorHeaderInfo &operator=(const GeneratorHeaderInfo &rhs) {
      if (this == &rhs) return *this;
      TObject::operator=(*this);
      return *this;
    };
    /** destructor **/
    virtual ~GeneratorHeaderInfo() {};

    /** methods to override **/
    virtual void Reset() = 0;
    
  protected:

    ClassDefOverride(GeneratorHeaderInfo, 1);
    
  };
    
  /*****************************************************************/
  /*****************************************************************/

  class CrossSectionInfo : public GeneratorHeaderInfo
  {

  public:
    
    /** default constructor **/
    CrossSectionInfo();
    /** copy constructor **/
    CrossSectionInfo(const CrossSectionInfo &rhs);
    /** operator= **/
    CrossSectionInfo &operator=(const CrossSectionInfo &rhs);
    /** destructor **/
    virtual ~CrossSectionInfo();

    /** getters **/
    Double_t GetCrossSection() const {return fCrossSection;};
    Double_t GetCrossSectionError() const {return fCrossSectionError;};
    Long64_t GetAcceptedEvents() const {return fAcceptedEvents;};
    Long64_t GetAttemptedEvents() const {return fAttemptedEvents;};

    /** setters **/
    void SetCrossSection(Double_t val) {fCrossSection = val;};
    void SetCrossSectionError(Double_t val) {fCrossSectionError = val;};
    void SetAcceptedEvents(Long64_t val) {fAcceptedEvents = val;};
    void SetAttemptedEvents(Long64_t val) {fAttemptedEvents = val;};

    /** methods to override **/
    void Print(Option_t *opt = "") const override;
    void Reset() override;

    /** statics **/
    static std::string KeyName() {return "cross-section";};
    
  protected:
    
    /** data members **/
    Double_t fCrossSection;       // Generated cross-section
    Double_t fCrossSectionError;  // Generated cross-section error
    Long64_t fAcceptedEvents;     // The number of events generated so far
    Long64_t fAttemptedEvents;    // The number of events attempted so far

    ClassDefOverride(CrossSectionInfo, 1);

  }; /** class CrossSectionInfo **/
  
  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_GENERATORHEADER_H_ */ 


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

#ifndef ALICEO2_EVENTGEN_CROSSSECTIONINFO_H_
#define ALICEO2_EVENTGEN_CROSSSECTIONINFO_H_

#include "GeneratorInfo.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  class CrossSectionInfo : public GeneratorInfo
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
    Double_t GetCrossSection()      const {return fCrossSection;};
    Double_t GetCrossSectionError() const {return fCrossSectionError;};
    Long64_t GetAcceptedEvents()    const {return fAcceptedEvents;};
    Long64_t GetAttemptedEvents()   const {return fAttemptedEvents;};

    /** setters **/
    void SetCrossSection(Double_t val)      {fCrossSection = val;};
    void SetCrossSectionError(Double_t val) {fCrossSectionError = val;};
    void SetAcceptedEvents(Long64_t val)    {fAcceptedEvents = val;};
    void SetAttemptedEvents(Long64_t val)   {fAttemptedEvents = val;};

    /** methods **/
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

#endif /* ALICEO2_EVENTGEN_CROSSSECTIONINFO_H_ */ 

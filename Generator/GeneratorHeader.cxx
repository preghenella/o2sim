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

#include "GeneratorHeader.h"
#include "CrossSectionInfo.h"
#include "HeavyIonInfo.h"
#include <iostream>

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  GeneratorHeader::GeneratorHeader() :
    TNamed("ALICEo2", "ALICEo2 Generator Header"),
    fTrackOffset(0),
    fNumberOfTracks(0),
    fNumberOfAttempts(0),
    fInfo()
  {
    /** default constructor **/
    
  }

  /*****************************************************************/

  GeneratorHeader::GeneratorHeader(const Char_t *name, const Char_t *title) :
    TNamed(name, title),
    fTrackOffset(0),
    fNumberOfTracks(0),
    fNumberOfAttempts(0),
    fInfo()
  {
    /** constructor **/

  }

  /*****************************************************************/

  GeneratorHeader::GeneratorHeader(const GeneratorHeader &rhs) :
    TNamed(rhs),
    fTrackOffset(rhs.fTrackOffset),
    fNumberOfTracks(rhs.fNumberOfTracks),
    fNumberOfAttempts(rhs.fNumberOfAttempts),
    fInfo(rhs.fInfo)
  {
    /** copy constructor **/

  }

  /*****************************************************************/

  GeneratorHeader &
  GeneratorHeader::operator=(const GeneratorHeader &rhs)
  {
    /** operator= **/
    
    if (this == &rhs) return *this;
    TNamed::operator=(rhs);
    fTrackOffset = rhs.fTrackOffset;
    fNumberOfTracks = rhs.fNumberOfTracks;
    fNumberOfAttempts = rhs.fNumberOfAttempts;
    fInfo = rhs.fInfo;
    return *this;
  }

  /*****************************************************************/

  GeneratorHeader::~GeneratorHeader()
  {
    /** default destructor **/

  }

  /*****************************************************************/

  void
  GeneratorHeader::Reset()
  {
    /** reset **/

    fTrackOffset = 0;
    fNumberOfTracks = 0;
    fNumberOfAttempts = 0;
    for (auto &info : fInfo) 
      info.second->Reset();
  }

  /*****************************************************************/

  void
  GeneratorHeader::Print(Option_t *opt) const
  {
    /** print **/

    auto name = GetName();
    auto offset = GetTrackOffset();
    auto ntracks = GetNumberOfTracks();
    std::cout << ">> generator: " << name << " | tracks: " << offset  << " -> " << offset + ntracks - 1 << std::endl;
    for (auto const &info : fInfo) 
      info.second->Print();
  }

  /*****************************************************************/
  
  CrossSectionInfo *
  GeneratorHeader::GetCrossSectionInfo() const
  {
    /** get cross-section info **/

    std::string key = CrossSectionInfo::KeyName();
    if (!fInfo.count(key)) return NULL;
    return dynamic_cast<CrossSectionInfo *>(fInfo.at(key));
  }
  
  /*****************************************************************/

  CrossSectionInfo *
  GeneratorHeader::AddCrossSectionInfo()
  {
    /** add cross-section info **/

    std::string key = CrossSectionInfo::KeyName();
    if (!fInfo.count(key))
      fInfo[key] = new CrossSectionInfo();
    return static_cast<CrossSectionInfo *>(fInfo.at(key));
  }
  
  /*****************************************************************/
  
  void
  GeneratorHeader::RemoveCrossSectionInfo()
  {
    /** remove cross-section info **/
    
    RemoveGeneratorInfo(CrossSectionInfo::KeyName());
  }
  
  /*****************************************************************/
  
  HeavyIonInfo *
  GeneratorHeader::GetHeavyIonInfo() const
  {
    /** get heavy-ion info **/

    std::string key = HeavyIonInfo::KeyName();
    if (!fInfo.count(key)) return NULL;
    return dynamic_cast<HeavyIonInfo *>(fInfo.at(key));
  }
  
  /*****************************************************************/

  HeavyIonInfo *
  GeneratorHeader::AddHeavyIonInfo()
  {
    /** add cross-section info **/

    std::string key = HeavyIonInfo::KeyName();
    if (!fInfo.count(key))
      fInfo[key] = new HeavyIonInfo();
    return static_cast<HeavyIonInfo *>(fInfo.at(key));
  }
  
  /*****************************************************************/
  
  void
  GeneratorHeader::RemoveHeavyIonInfo()
  {
    /** remove cross-section info **/
    
    RemoveGeneratorInfo(HeavyIonInfo::KeyName());
  }
  
  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

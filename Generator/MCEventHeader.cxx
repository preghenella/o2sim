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

#include "MCEventHeader.h"
#include "FairRootManager.h"
#include "GeneratorHeader.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  MCEventHeader::MCEventHeader() :
    FairMCEventHeader(),
    fGeneratorHeaders()
  {
    /** default constructor **/

  }

  /*****************************************************************/

  MCEventHeader::MCEventHeader(const MCEventHeader &rhs) :
    FairMCEventHeader(rhs),
    fGeneratorHeaders(rhs.fGeneratorHeaders)
  {
    /** copy constructor **/

  }

  /*****************************************************************/

  MCEventHeader &
  MCEventHeader::operator=(const MCEventHeader &rhs)
  {
    /** operator= **/

    if (this == &rhs) return *this;
    FairMCEventHeader::operator=(rhs);
    fGeneratorHeaders = rhs.fGeneratorHeaders;
    return *this;
  }

  /*****************************************************************/

  MCEventHeader::~MCEventHeader()
  {
    /** default destructor **/

  }

  /*****************************************************************/

  void
  MCEventHeader::Reset()
  {
    /** reset **/

    fGeneratorHeaders.clear();
    FairMCEventHeader::Reset();
  }

  /*****************************************************************/

  void
  MCEventHeader::Print(Option_t *opt) const
  {
    /** print **/

    auto eventId = GetEventID();
    std::cout << "> event-id: " << eventId << " | N.primaries: " << GetNPrim() << std::endl;
    for (auto const &header : fGeneratorHeaders) 
      header->Print();
  }

  /*****************************************************************/

  void
  MCEventHeader::AddHeader(GeneratorHeader *header)
  {
    /** add header **/

    fGeneratorHeaders.push_back(new GeneratorHeader(*header));
  }
  
  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

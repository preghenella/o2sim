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

#include "CrossSectionInfo.h"
#include <iostream>

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/
    
  CrossSectionInfo::CrossSectionInfo() :
    GeneratorInfo(),
    fCrossSection(0.),
    fCrossSectionError(0.),
    fAcceptedEvents(0),
    fAttemptedEvents(0)
  {
    /** default constructor **/
    
  }

  /*****************************************************************/

  CrossSectionInfo::CrossSectionInfo(const CrossSectionInfo &rhs) :
    GeneratorInfo(rhs),
    fCrossSection(rhs.fCrossSection),
    fCrossSectionError(rhs.fCrossSectionError),
    fAcceptedEvents(rhs.fAcceptedEvents),
    fAttemptedEvents(rhs.fAttemptedEvents)
  {
    /** copy constructor **/

  }

  /*****************************************************************/

  CrossSectionInfo &
  CrossSectionInfo::operator=(const CrossSectionInfo &rhs)
  {
    /** operator= **/
    
    if (this == &rhs) return *this;
    GeneratorInfo::operator=(rhs);
    fCrossSection = rhs.fCrossSection;
    fCrossSectionError = rhs.fCrossSectionError;
    fAcceptedEvents = rhs.fAcceptedEvents;
    fAttemptedEvents = rhs.fAttemptedEvents;
    return *this;
  }

  /*****************************************************************/

  CrossSectionInfo::~CrossSectionInfo()
  {
    /** default destructor **/

  }

  /*****************************************************************/

  void
  CrossSectionInfo::Reset()
  {
    /** reset **/

    fCrossSection = 0.;
    fCrossSectionError = 0.;
    fAcceptedEvents = 0;
    fAttemptedEvents = 0;
  }

  /*****************************************************************/

  void
  CrossSectionInfo::Print(Option_t *opt) const
  {
    /** print **/

    std::cout << ">>> sigma: " << fCrossSection << " +- " << fCrossSectionError << " (pb)"
	      << " | accepted / attempted: " << fAcceptedEvent << " / " << fAttemptedEvents
	      << std::endl;

  }

  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

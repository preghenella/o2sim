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

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  MCEventHeader::MCEventHeader() :
    FairMCEventHeader(),
    fRoby(666)
  {
    /** default constructor **/

  }

  /*****************************************************************/

  MCEventHeader::MCEventHeader(const MCEventHeader &rhs) :
    FairMCEventHeader(rhs),
    fRoby(rhs.fRoby)
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
    fRoby = rhs.fRoby;
    return *this;
  }

  /*****************************************************************/

  MCEventHeader::~MCEventHeader()
  {
    /** default destructor **/

  }

  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

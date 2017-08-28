
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

namespace o2
{
namespace eventgen
{

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

  protected:

    ClassDefOverride(MCEventHeader, 1);

    Int_t fRoby;
    
  }; /** class MCEventHeader **/
  
  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_MCEVENTHEADER_H_ */ 

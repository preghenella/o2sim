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
    fNumberOfAttempts(0)
  {
    /** default constructor **/

  }

  /*****************************************************************/

  GeneratorHeader::GeneratorHeader(const Char_t *name, const Char_t *title) :
    TNamed(name, title),
    fTrackOffset(0),
    fNumberOfTracks(0),
    fNumberOfAttempts(0)
  {
    /** constructor **/

  }

  /*****************************************************************/

  GeneratorHeader::GeneratorHeader(const GeneratorHeader &rhs) :
    TNamed(rhs),
    fTrackOffset(rhs.fTrackOffset),
    fNumberOfTracks(rhs.fNumberOfTracks),
    fNumberOfAttempts(rhs.fNumberOfAttempts)
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
  }

  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

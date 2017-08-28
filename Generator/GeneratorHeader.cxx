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

  GeneratorHeader::GeneratorHeader(const TString &name, const TString &title) :
    TNamed(name, title),
    fOffset(0),
    fNTracks(0)
  {
    /** default constructor **/

  }

  /*****************************************************************/

  GeneratorHeader::~GeneratorHeader()
  {
    /** default destructor **/

  }

  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "TriggerTGenerator.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  TriggerTGenerator::TriggerTGenerator() :
    Trigger()
  {
    /** default constructor **/
  }

  /*****************************************************************/

  TriggerTGenerator::~TriggerTGenerator()
  {
    /** default destructor **/
  }
  
  /*****************************************************************/

  Bool_t
  TriggerTGenerator::TriggerEvent(TClonesArray *particles, TGenerator *generator)
  {
    /** trigger event **/

    /** check active **/
    if (!IsActive()) return kFALSE;
    /* trigger */
    if (!IsTriggered(particles, generator)) return kFALSE;
    /* downscale */
    if (IsDownscaled()) return kFALSE;

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /* namespace eventgen */
} /* namespace o2 */

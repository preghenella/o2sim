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

#include "GeneratorManagerDelegate.h"

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  GeneratorManagerDelegate::GeneratorManagerDelegate() :
    ConfigurationManager(),
    fGenerator(NULL)
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("status", "");

  }

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

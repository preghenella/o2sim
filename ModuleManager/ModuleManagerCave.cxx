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

#include "ModuleManagerCave.h"
#include "DetectorsPassive/Cave.h"
#include "FairLogger.h"

namespace o2sim
{

  /*****************************************************************/
  
  ModuleManagerCave::ModuleManagerCave() :
    ModuleManagerDelegate()
  {
    /** deafult constructor **/

    RegisterValue("geometryFileName", "cave.geo");
  }

  /*****************************************************************/

  Bool_t
  ModuleManagerCave::Init()
  {
    /** init **/

    /** check active **/
    if (!GetValue("status").Contains("active"))
      return kTRUE;

    /** create module **/ 
    o2::Passive::Cave *module = new o2::Passive::Cave("CAVE");

    /** configure module **/
    module->SetGeometryFileName(GetValue("geometryFileName"));

    /** success **/
    fModule = module;
    return kTRUE;
  }
  
  /*****************************************************************/

} /** namespace o2sim **/

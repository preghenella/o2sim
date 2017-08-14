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

#include "ModuleManagerTPC.h"
#include "TPCSimulation/Detector.h"

namespace o2sim
{

  /*****************************************************************/
  
  ModuleManagerTPC::ModuleManagerTPC() :
    ModuleManagerDelegate()
  {
    /** deafult constructor **/
    
    RegisterValue("geometryFileName", "TPCGeometry.root");
  }

  /*****************************************************************/

  FairModule *
  ModuleManagerTPC::Init() const
  {
    /** init **/

    /** create module **/
    o2::TPC::Detector *module = new o2::TPC::Detector("TPC", kTRUE);
    
    /** configure module **/
    module->SetGeoFileName(GetValue("geometryFileName"));

    /** success **/
    return module;
  }
  
  /*****************************************************************/

} /** namespace o2sim **/

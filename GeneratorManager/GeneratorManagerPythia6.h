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

#ifndef ALICEO2SIM_GENERATORMANAGERPYTHIA6_H_
#define ALICEO2SIM_GENERATORMANAGERPYTHIA6_H_

#include "GeneratorManagerDelegate.h"

class TPythia6;

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class GeneratorManagerPythia6 : public GeneratorManagerDelegate
  {

  public:

    enum ETune_t {
      kDefault     = 0,
      kPerugia0    = 320,
      kPerugia2011 = 350
    };
    
    enum EProcess_t {
      kMinimumBias,
      kJets,
      kDirectGamma,
      kCharm,
      kBeauty,
      kNProcesses
    };
    
    /** default constructor **/
    GeneratorManagerPythia6();

    /** methods **/
    virtual Bool_t Init() override;

  private:

    Bool_t ConfigureBaseline(TPythia6 *py6);
    Bool_t ConfigureProcess(TPythia6 *py6);
    
    ClassDefOverride(GeneratorManagerPythia6, 1)
      
  }; /** class GeneratorManagerPythia6 **/

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

#endif /* ALICEO2SIM_GENERATORMANAGERPYTHIA6_H_ */

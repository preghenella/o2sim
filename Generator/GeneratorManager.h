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

#ifndef ALICEO2SIM_GENERATORMANAGER_H_
#define ALICEO2SIM_GENERATORMANAGER_H_

#include "Core/RunManagerDelegate.h"

namespace o2 {
  namespace eventgen {
    class PrimaryGenerator;
  }
}

namespace o2eg = o2::eventgen;

namespace o2sim {
  
  /*****************************************************************/
  /*****************************************************************/
  
  class GeneratorManager : public RunManagerDelegate
  {
    
  public:
    
    /** default constructor **/
    GeneratorManager();
    
    /** methods **/
    Bool_t Init() const override;
    Bool_t Terminate() const override;
    
  private:

    Bool_t ConfigurePrimaryGenerator(o2eg::PrimaryGenerator *primGen) const;
    Bool_t SetupInteractionDiamond(o2eg::PrimaryGenerator *primGen) const;
    
    ClassDefOverride(GeneratorManager, 1)
      
  }; /** class GeneratorManager **/

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_GENERATORMANAGER_H_ */

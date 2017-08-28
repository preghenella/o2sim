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

#ifndef ALICEO2SIM_GENERATORMANAGERPYTHIA_H_
#define ALICEO2SIM_GENERATORMANAGERPYTHIA_H_

#include "Core/GeneratorManagerDelegate.h"
#include <fstream>

namespace o2 {
  namespace eventgen {
    class GeneratorHepMC;
  }
}

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class GeneratorManagerPythia : public GeneratorManagerDelegate
  {

  public:

    /** default constructor **/
    GeneratorManagerPythia();

    /** methods **/
    FairGenerator *Init() const override;
    Bool_t Terminate() const override;
    
  private:

    /** init methods **/
    Bool_t InitTrigger(o2::eventgen::GeneratorHepMC *generator) const;
    Bool_t InitInterface(o2::eventgen::GeneratorHepMC *generator, std::string &configFileName, Int_t &pid) const;
    
    /** configuration methods **/
    Bool_t ConfigureCollision(std::ostream &config) const;
    Bool_t ConfigureBaseline(std::ostream &config) const;
    Bool_t ConfigureTune(std::ostream &config) const; 
    Bool_t ConfigureProcess(std::ostream &config) const;

    /** get methods **/
    Bool_t GetPtHat(Double_t &min, Double_t &max) const;

    /** terminate methods **/
    Bool_t TerminateTPythia6() const;
    Bool_t TerminateAGILe() const;
    Bool_t TerminateTPythia8() const;
    Bool_t TerminateSacrifice() const;

    ClassDefOverride(GeneratorManagerPythia, 1)
      
  }; /** class GeneratorManagerPythia **/

  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

#endif /* ALICEO2SIM_GENERATORMANAGERPYTHIA_H_ */

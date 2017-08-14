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

#ifndef ALICEO2SIM_GENERATORMANAGERDELEGATE_H_
#define ALICEO2SIM_GENERATORMANAGERDELEGATE_H_

#include "Core/ConfigurationManager.h"
#include "TLorentzVector.h"

class FairGenerator;
class TLorentzVector;

namespace o2sim {

  /*****************************************************************/
  /*****************************************************************/

  class GeneratorManagerDelegate : public ConfigurationManager
  {

  public:

    /** default constructor **/
    GeneratorManagerDelegate();

    /** methods **/
    virtual FairGenerator *Init() const = 0;
    virtual Bool_t Terminate() const = 0;

  protected:

    Bool_t GetBeamP(TString beam, Double_t &p) const; 
    Bool_t GetBeamAZ(TString beam, Int_t &a, Int_t &z) const;
    Bool_t GetBeamVector(TString beam, TLorentzVector &lv) const;

    Bool_t GetCMSVector(TLorentzVector &lv) const;
    Bool_t GetCMSEnergy(Double_t &e) const;
    Bool_t GetCMSRapidity(Double_t &y) const;
    
  private:

    ClassDefOverride(GeneratorManagerDelegate, 1)
      
  }; /** class GeneratorManagerDelegate **/
  
  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

#endif /* ALICEO2SIM_GENERATORMANAGERDELEGATE_H_ */

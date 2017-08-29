
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

#ifndef ALICEO2_EVENTGEN_HEAVYIONINFO_H_
#define ALICEO2_EVENTGEN_HEAVYIONINFO_H_

#include "GeneratorInfo.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  class HeavyIonInfo : public GeneratorInfo
  {

  public:
    
    /** default constructor **/
    HeavyIonInfo();
    /** copy constructor **/
    HeavyIonInfo(const HeavyIonInfo &rhs);
    /** operator= **/
    HeavyIonInfo &operator=(const HeavyIonInfo &rhs);
    /** destructor **/
    virtual ~HeavyIonInfo();

    /** getters **/
    Int_t    GetNcollHard()       const {return fNcollHard;};
    Int_t    GetNpartProj()       const {return fNpartProj;};
    Int_t    GetNpartTarg()       const {return fNpartTarg;};
    Int_t    GetNcoll()           const {return fNcoll;};
    Int_t    GetNspecNeut()       const {return fNspecNeut;};
    Int_t    GetNspecProt()       const {return fNspecProt;};
    Double_t GetImpactParameter() const {return fImpactParameter;};
    Double_t GetEventPlaneAngle() const {return fEventPlaneAngle;};
    Double_t GetEccentricity()    const {return fEccentricity;};
    Double_t GetSigmaNN()         const {return fSigmaNN;};
    Double_t GetCentrality()      const {return fCentrality;};

    /** setters **/
    void SetNcollHard(Int_t val)          {fNcollHard = val;};
    void SetNpartProj(Int_t val)          {fNpartProj = val;};
    void SetNpartTarg(Int_t val)          {fNpartTarg = val;};
    void SetNcoll(Int_t val)              {fNcoll = val;};
    void SetNspecNeut(Int_t val)          {fNspecNeut = val;};
    void SetNspecProt(Int_t val)          {fNspecProt = val;};
    void SetImpactParameter(Double_t val) {fImpactParameter = val;};
    void SetEventPlaneAngle(Double_t val) {fEventPlaneAngle = val;};
    void SetEccentricity(Double_t val)    {fEccentricity = val;};
    void SetSigmaNN(Double_t val)         {fSigmaNN = val;};
    void SetCentrality(Double_t val)      {fCentrality = val;};

    /** methods **/
    void Print(Option_t *opt = "") const override;
    void Reset() override;
    
    /** statics **/
    static std::string KeyName() {return "heavy-ion";};
    
  protected:

    /** data members **/
    Int_t    fNcollHard;       // Number of hard collisions
    Int_t    fNpartProj;       // Number of participating nucleons in the projectile
    Int_t    fNpartTarg;       // Number of participating nucleons in the target
    Int_t    fNcoll;           // Number of collisions
    Int_t    fNspecNeut;       // Number of spectator neutrons
    Int_t    fNspecProt;       // Number of spectator protons
    Double_t fImpactParameter; // Impact parameter
    Double_t fEventPlaneAngle; // Event plane angle
    Double_t fEccentricity;    // Eccentricity
    Double_t fSigmaNN;         // Assumed nucleon-nucleon cross-section
    Double_t fCentrality;      // Centrality    
    
    ClassDefOverride(HeavyIonInfo, 1);

  }; /** class HeavyIonInfo **/

  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_HEAVYIONINFO_H_ */ 

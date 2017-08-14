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
    ConfigurationManager()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("projectile_P");
    RegisterValue("projectile_AZ");
    RegisterValue("target_P");
    RegisterValue("target_AZ");
    RegisterValue("decay_table", "$O2SIM_ROOT/data/decaytable.dat");

  }

  /*****************************************************************/

  Bool_t
  GeneratorManagerDelegate::GetBeamP(TString beam, Double_t &p) const
  {
    /** get beam P **/

    /** check value **/
    TString value = GetValue(beam + "_P");
    if (!value.IsDigit() && !value.IsFloat()) {
      LOG(ERROR) << "Invalid " << beam << " momentum: " << value << std::endl;
      return kFALSE;
    }
    /** success **/
    p = value.Atof();
    return kTRUE;
  }
    
  /*****************************************************************/

  Bool_t
  GeneratorManagerDelegate::GetBeamAZ(TString beam, Int_t &a, Int_t &z) const
  {
    /** get beam (A, Z) **/

    /** check values **/
    Int_t az[2];
    if (!ParseValue(beam + "_AZ", az, 2)) {
      LOG(ERROR) << "Cannot parse " << beam << " (A,Z): " << GetValue(beam + "_AZ") << std::endl;
      return kFALSE;
    }
    if (az[0] <= 0 || az[1] <= 0 || az[0] < az[1]) {
      LOG(ERROR) << "Invalid " << beam << " (A,Z): " << "(" << az[0] << "," << az[1] << ")" << std::endl;
      return kFALSE;
    }
    /** success **/
    a = az[0]; z = az[1];
    return kTRUE;
  }
    
  /*****************************************************************/

  Bool_t
  GeneratorManagerDelegate::GetBeamVector(TString beam, TLorentzVector &lv) const
  {
    /** get beam vector **/

    /** check values **/
    Double_t p, m = 9.38271999999999995e-01; // [WARNING] assumes proton mass for the time being
    Int_t a, z;
    if (!GetBeamP(beam, p)) return kFALSE;
    if (!GetBeamAZ(beam, a, z)) return kFALSE;
    /** scale momentum for A, Z **/
    p *= ((Double_t)z / (Double_t)a);
    /** success **/
    lv.SetXYZM(0., 0., p, m);
    return kTRUE;
  }

  /*****************************************************************/
  
  Bool_t
  GeneratorManagerDelegate::GetCMSVector(TLorentzVector &lv) const
  {
    /** get CMS lorentz vector **/

    /** check values **/
    TLorentzVector plv, tlv;
    if (!GetBeamVector("projectile", plv)) return kFALSE;
    if (!GetBeamVector("target", tlv)) return kFALSE;
    /** success **/
    lv = plv + tlv;
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerDelegate::GetCMSEnergy(Double_t &e) const
  {
    /** get CMS energy **/

    /** check value **/
    TLorentzVector lv;
    if (!GetCMSVector(lv)) return kFALSE;
    /** success **/
    e = lv.Mag();
    return kTRUE;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerDelegate::GetCMSRapidity(Double_t &y) const
  {
    /** get CMS energy **/

    /** check value **/
    TLorentzVector lv;
    if (!GetCMSVector(lv)) return kFALSE;
    /** success **/
    y = lv.Rapidity();
    return kTRUE;
  }
  
  /*****************************************************************/
  /*****************************************************************/
  
} /** namespace o2sim **/

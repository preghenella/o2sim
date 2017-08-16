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

#include "GeneratorManagerBox.h"
#include "FairBoxGenerator.h"

namespace o2sim
{

  /*****************************************************************/
  /*****************************************************************/
  
  GeneratorManagerBox::GeneratorManagerBox() :
    GeneratorManagerDelegate()
  {
    /** deafult constructor **/

    /** register values **/
    RegisterValue("multiplicity");
    RegisterValue("pdg_code");
    RegisterValue("momentum");
    RegisterValue("pt");
    RegisterValue("ekin");
    RegisterValue("phi", "0., 360.");
    RegisterValue("eta");
    RegisterValue("rapidity");
    RegisterValue("theta");
    RegisterValue("vertex_xyz");
    RegisterValue("debug", "false");
  }

  /*****************************************************************/

  FairGenerator *
  GeneratorManagerBox::Init() const
  {
    /** init **/

    Int_t multiplicity, pdg_code;
    Double_t momentum[2], pt[2], ekin[2], phi[2], eta[2], rapidity[2], theta[2], vertex_xyz[3];

    /** multiplicity **/
    if (!GetValue("multiplicity", multiplicity) || multiplicity < 1) {
      LOG(ERROR) << "Invalid multiplicity" << std::endl;
      return NULL;
    }
    /** pdg code **/
    if (!GetValue("pdg_code", pdg_code) || pdg_code == 0) {
      LOG(ERROR) << "Invalid PDG code" << std::endl;
      return NULL;
    }

    /** create generator **/ 
    FairBoxGenerator *generator = new FairBoxGenerator();
    generator->SetMultiplicity(multiplicity);
    generator->SetPDGType(pdg_code);

    /** setup generator **/

    /** momentum **/
    if (!IsNull("momentum")) {
      if (!GetValue("momentum", momentum, 2) || momentum[0] > momentum[1]) {
	LOG(ERROR) << "Invalid momentum range" << std::endl;
	return NULL;
      }
      generator->SetPRange(momentum[0], momentum[1]);
    }
    /** pt **/
    if (!IsNull("pt")) {
      if (!GetValue("pt", pt, 2) || pt[0] > pt[1]) {
	LOG(ERROR) << "Invalid pt range" << std::endl;
	return NULL;
      }
      generator->SetPtRange(pt[0], pt[1]);
    }
    /** E kinetic **/
    if (!IsNull("ekin")) {
      if (!GetValue("ekin", ekin, 2) || ekin[0] > ekin[1]) {
	LOG(ERROR) << "Invalid ekin range" << std::endl;
	return NULL;
      }
      generator->SetEkinRange(ekin[0], ekin[1]);
    }
    /** phi **/
    if (!IsNull("phi")) {
      if (!GetValue("phi", phi, 2) || phi[0] > phi[1] || phi[0] < 0. || phi[1] > 360.) {
	LOG(ERROR) << "Invalid phi range" << std::endl;
	return NULL;
      }
      generator->SetPhiRange(phi[0], phi[1]);
    }
    /** eta **/
    if (!IsNull("eta")) {
      if (!GetValue("eta", eta, 2) || eta[0] > eta[1]) {
	LOG(ERROR) << "Invalid eta range" << std::endl;
	return NULL;
      }
      generator->SetEtaRange(eta[0], eta[1]);
    }
    /** rapidity **/
    if (!IsNull("rapidity")) {
      if (!GetValue("rapidity", rapidity, 2) || rapidity[0] > rapidity[1]) {
	LOG(ERROR) << "Invalid rapidity range" << std::endl;
	return NULL;
      }
      generator->SetYRange(rapidity[0], rapidity[1]);
    }
    /** theta **/
    if (!IsNull("theta")) {
      if (!GetValue("theta", theta, 2) || theta[0] > theta[1]) {
	LOG(ERROR) << "Invalid theta range" << std::endl;
	return NULL;
      }
      generator->SetEtaRange(theta[0], theta[1]);
    }
    /** vertex_xyz **/
    if (!IsNull("vertex_xyz")) {
      if (!GetValue("vertex_xyz", vertex_xyz, 3)) {
	LOG(ERROR) << "Invalid vertex_xyz" << std::endl;
	return NULL;
      }
      generator->SetXYZ(vertex_xyz[0], vertex_xyz[1], vertex_xyz[2]);
    }
    /** debug **/
    if (IsValue("debug", "true")) {
      generator->SetDebug(kTRUE);
    }
    
    /** success **/
    return generator;
  }
  
  /*****************************************************************/

  Bool_t
  GeneratorManagerBox::Terminate() const
  {
    /** terminate **/

    /** success **/
    return kTRUE;
  }

  /*****************************************************************/
  /*****************************************************************/

} /** namespace o2sim **/

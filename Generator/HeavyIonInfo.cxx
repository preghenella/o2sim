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

#include "HeavyIonInfo.h"
#include <iostream>

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/
    
  HeavyIonInfo::HeavyIonInfo() :
    GeneratorInfo(),
    fNcollHard(0),
    fNpartProj(0),
    fNpartTarg(0),
    fNcoll(0),
    fNspecNeut(0),
    fNspecProt(0),
    fImpactParameter(0.),
    fEventPlaneAngle(0.),
    fEccentricity(0.),
    fSigmaNN(0.),
    fCentrality(0.)
  {
    /** default constructor **/
    
  }

  /*****************************************************************/

  HeavyIonInfo::HeavyIonInfo(const HeavyIonInfo &rhs) :
    GeneratorInfo(rhs),
    fNcollHard(rhs.fNcollHard),
    fNpartProj(rhs.fNpartProj),
    fNpartTarg(rhs.fNpartTarg),
    fNcoll(rhs.fNcoll),
    fNspecNeut(rhs.fNspecNeut),
    fNspecProt(rhs.fNspecProt),
    fImpactParameter(rhs.fImpactParameter),
    fEventPlaneAngle(rhs.fEventPlaneAngle),
    fEccentricity(rhs.fEccentricity),
    fSigmaNN(rhs.fSigmaNN),
    fCentrality(rhs.fCentrality)
  {
    /** copy constructor **/

  }

  /*****************************************************************/

  HeavyIonInfo &
  HeavyIonInfo::operator=(const HeavyIonInfo &rhs)
  {
    /** operator= **/
    
    if (this == &rhs) return *this;
    GeneratorInfo::operator=(rhs);
    fNcollHard = rhs.fNcollHard;
    fNpartProj = rhs.fNpartProj;
    fNpartTarg = rhs.fNpartTarg;
    fNcoll = rhs.fNcoll;
    fNspecNeut = rhs.fNspecNeut;
    fNspecProt = rhs.fNspecProt;
    fImpactParameter = rhs.fImpactParameter;
    fEventPlaneAngle = rhs.fEventPlaneAngle;
    fEccentricity = rhs.fEccentricity;
    fSigmaNN = rhs.fSigmaNN;
    fCentrality = rhs.fCentrality;
    return *this;
  }

  /*****************************************************************/

  HeavyIonInfo::~HeavyIonInfo()
  {
    /** default destructor **/

  }

  /*****************************************************************/

  void
  HeavyIonInfo::Fill(HepMC::GenHeavyIonPtr &hi)
  {
    /** fill **/

  }

  /*****************************************************************/

  void
  HeavyIonInfo::Reset()
  {
    /** reset **/

    fNcollHard = 0;
    fNpartProj = 0;
    fNpartTarg = 0;
    fNcoll = 0;
    fNspecNeut = 0;
    fNspecProt = 0;
    fImpactParameter = 0.;
    fEventPlaneAngle = 0.;
    fEccentricity = 0.;
    fSigmaNN = 0.;
    fCentrality = 0.;
  }

  /*****************************************************************/

  void
  HeavyIonInfo::Print(Option_t *opt) const
  {
    /** print **/

    std::cout << ">>> Ncoll: " << fNcoll
	      << " | Npart: " << fNpartProj + fNpartTarg
	      << " | b: " << fImpactParameter << " (fm)"
	      << " | cent: " << fCentrality << " (\%)"
	      << std::endl;
  }

  /*****************************************************************/
  /*****************************************************************/
    
} /* namespace eventgen */
} /* namespace o2 */

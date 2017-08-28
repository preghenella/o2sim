// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \author R+Preghenella - June 2017

#ifndef ALICEO2_EVENTGEN_PRIMARYGENERATOR_H_
#define ALICEO2_EVENTGEN_PRIMARYGENERATOR_H_

#include "FairPrimaryGenerator.h"

class FairGenericStack;
class TClonesArray;

namespace o2
{
namespace eventgen
{

  class GeneratorHeader;
  
  /*****************************************************************/
  /*****************************************************************/
  
  class PrimaryGenerator : public FairPrimaryGenerator
  {
    
  public:
    
    /** default constructor **/
    PrimaryGenerator();
    /** destructor **/
    virtual ~PrimaryGenerator();

    /** Public method GenerateEvent
	To be called at the beginning of each event from FairMCApplication.
	Generates an event vertex and calls the ReadEvent methods from the
	registered generators.
	*@param pStack The particle stack
	*@return kTRUE if successful, kFALSE if not
	**/
    Bool_t GenerateEvent(FairGenericStack *stack) override;
    
    /** Public method AddTrack
	Adding a track to the MC stack. To be called within the ReadEvent
	methods of the registered generators.
	*@param pdgid Particle ID (PDG code)
	*@param px,py,pz Momentum coordinates [GeV]
	*@param vx,vy,vz Track origin relative to event vertex
	**/
    void AddTrack(Int_t pdgid, Double_t px, Double_t py, Double_t pz,
		  Double_t vx, Double_t vy, Double_t vz,
		  Int_t parent = -1, Bool_t wanttracking = true,
		  Double_t e = -9e9, Double_t tof = 0.,
		  Double_t weight = 0., TMCProcess proc = kPPrimary) override;
    
    /** Public method AddTrack
	Adding a track to the MC stack. To be called within the ReadEvent
	methods of the registered generators.
	*@param status Status code
	*@param pdgid Particle ID (PDG code)
	*@param doTracking Tracking flag
	*@param weight Track weight
	*@param px,py,pz,et FourMomentum coordinates [GeV]
	*@param vx,vy,vz,vt Track origin relative to event vertex
	*@param firstMother,lastMother First and last mother label
	*@param firstDaughter,lastDaughter First and last daughter label
	**/
    void AddTrack(Int_t status, Int_t pdgid, Bool_t doTracking, Double_t weight, 
		  Double_t px, Double_t py, Double_t pz, Double_t et,
		  Double_t vx, Double_t vy, Double_t vz, Double_t vt,
		  Int_t firstMother, Int_t lastMother, Int_t firstDaughter, Int_t lastDaughter);

    /** Public method AddHeader
	Adding a generator header to the MC event header.
	To be called after all tracks have been added.
    **/
    void AddHeader(GeneratorHeader *header);
    
    /** set interaction diamond position **/
    void SetInteractionDiamond(const Double_t *xyz, const Double_t *sigmaxyz, Bool_t smear = kTRUE);
    
  protected:
    
    /** copy constructor **/
    PrimaryGenerator(const PrimaryGenerator &);
    /** operator= **/
    PrimaryGenerator &operator=(const PrimaryGenerator &);

    ClassDefOverride(PrimaryGenerator, 1);

  }; /** class PrimaryGenerator **/

  /*****************************************************************/
  /*****************************************************************/
  
} /* namespace eventgen */
} /* namespace o2 */

#endif /* ALICEO2_EVENTGEN_PRIMARYGENERATOR_H_ */

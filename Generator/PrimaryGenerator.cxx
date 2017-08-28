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

#include "PrimaryGenerator.h"
#include "FairGenericStack.h"
#include "FairGenerator.h"
#include "MCEventHeader.h"
#include "FairLogger.h"
#include "GeneratorHeader.h"
#include "TClonesArray.h"

namespace o2
{
namespace eventgen
{

  /*****************************************************************/
  /*****************************************************************/

  PrimaryGenerator::PrimaryGenerator() :
    FairPrimaryGenerator("ALICEo2", "ALICEo2 Primary Generator")
  {
    /** default constructor **/

  }

  /*****************************************************************/

  PrimaryGenerator::~PrimaryGenerator()
  {
    /** default destructor **/

  }

  /*****************************************************************/

  Bool_t
  PrimaryGenerator::GenerateEvent(FairGenericStack *stack)
  {
    /** generate event **/

    /** initialise **/
    fStack = stack;
    fNTracks = 0;
    fEvent->Reset();

    /** create event vertex **/
    MakeVertex();
    fEvent->SetVertex(fVertex);

    /** read event from all generators **/
    fListIter->Reset();
    while (TObject *obj = fListIter->Next()) {
      FairGenerator *generator = dynamic_cast<FairGenerator *>(obj);
      if (!generator) return kFALSE;
      fMCIndexOffset = fNTracks; // number tracks before generator is called
      /** read event **/
      if (!generator->ReadEvent(this)) {
        LOG(ERROR) << "ReadEvent failed for generator " << generator->GetName() << std::endl;
        return kFALSE;
      }
    }
    fEvent->SetNPrim(fNTracks);
    
    fTotPrim += fNTracks; // screen output

    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/

  void
  PrimaryGenerator::AddTrack(Int_t pdgid, Double_t px, Double_t py, Double_t pz,
			     Double_t vx, Double_t vy, Double_t vz,
			     Int_t parent, Bool_t wanttracking,
			     Double_t e, Double_t tof, Double_t weight, TMCProcess proc)
  {
    /** add track **/

    AddTrack(0, pdgid, wanttracking, weight, px, py, pz, e, vx, vy, vz, tof, parent, -1, -1, -1);
  }

  /*****************************************************************/

  void
  PrimaryGenerator::AddTrack(Int_t status, Int_t pdgid, Bool_t doTracking, Double_t weight, 
			     Double_t px, Double_t py, Double_t pz, Double_t et,
			     Double_t vx, Double_t vy, Double_t vz, Double_t vt,
			     Int_t firstMother, Int_t lastMother, Int_t firstDaughter, Int_t lastDaughter)
  {
    /** add track **/

    /** add vertex to track vertex **/
    vx += fVertex.X();
    vy += fVertex.Y();
    vz += fVertex.Z();

    /** rotate (TBD) **/
    /** convert K0 (TBD) **/
    /** check known PDG (TBD) **/

    /** set parameters before push **/
    doTracking &= fdoTracking;
    Double_t polx = 0., poly = 0., polz = 0.;
    Int_t ntr = 0;

    /** apply index offset **/
    firstMother += fMCIndexOffset;
    lastMother += fMCIndexOffset;
    firstDaughter += fMCIndexOffset;
    lastDaughter += fMCIndexOffset;
    
    /** add track to the stack **/
    fStack->PushTrack(doTracking, firstMother, pdgid, px, py, pz, et, vx, vy, vz, vt, polx, poly, polz, kPPrimary, ntr, weight, status, firstMother);
    fNTracks++;
  }

  /*****************************************************************/

  void
  PrimaryGenerator::AddHeader(GeneratorHeader *header)
  {
    /** add header **/

    /** setup header **/
    header->SetTrackOffset(fMCIndexOffset);
    header->SetNumberOfTracks(fNTracks - fMCIndexOffset);

    /** check o2 event header **/
    auto o2event = dynamic_cast<MCEventHeader *>(fEvent);
    if (!o2event) return;
    o2event->AddHeader(header);
    
  }
  
  /*****************************************************************/

  void
  PrimaryGenerator::SetInteractionDiamond(const Double_t *xyz, const Double_t *sigmaxyz, Bool_t smear)
  {
    /** set interaction diamond **/

    SetBeam(xyz[0], xyz[1], sigmaxyz[0], sigmaxyz[1]);
    SetTarget(xyz[2], sigmaxyz[2]);
    SmearGausVertexXY(smear);
    SmearGausVertexZ(smear);
  }

  /*****************************************************************/
  /*****************************************************************/  
   
} /* namespace eventgen */
} /* namespace o2 */

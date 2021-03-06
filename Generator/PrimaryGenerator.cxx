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
#include "FairMCEventHeader.h"
#include "MCEventHeader.h"
#include "FairLogger.h"
#include "GeneratorHeader.h"
#include "TFile.h"
#include "TTree.h"

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
  PrimaryGenerator::GenerateEvent(FairGenericStack *pStack)
  {
    /** generate event **/

    /** normal generation if no embedding **/
    if (!mEmbedTree) return FairPrimaryGenerator::GenerateEvent(pStack);

    /** this is for embedding **/
    
    /** setup interaction diamond **/
    mEmbedTree->GetEntry(mEmbedCounter);
    SetInteractionDiamond(mEmbedEvent);

    /** generate event **/
    if (!FairPrimaryGenerator::GenerateEvent(pStack)) return kFALSE;

    /** add embedding info to event header **/
    auto o2event = dynamic_cast<MCEventHeader *>(fEvent);
    if (o2event) {
      o2event->SetEmbeddingFileName(mEmbedFile->GetName());
      o2event->SetEmbeddingEventCounter(mEmbedCounter);
    }
    
    /** increment embedding counter **/
    mEmbedCounter++;
    mEmbedCounter %= mEmbedEntries;

    /** success **/
    return kTRUE;
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
    SmearVertexXY(kFALSE);
    SmearVertexZ(kFALSE);
    SmearGausVertexXY(smear);
    SmearGausVertexZ(smear);
  }

  /*****************************************************************/

  void
  PrimaryGenerator::SetInteractionDiamond(const FairMCEventHeader *event)
  {
    /** set interaction diamond **/

    Double_t xyz[3] = {event->GetX(), event->GetY(), event->GetZ()};
    Double_t sigmaxyz[3] = {0., 0., 0.};
    SetInteractionDiamond(xyz, sigmaxyz, kFALSE);
    
  }

  /*****************************************************************/

  Bool_t
  PrimaryGenerator::EmbedInto(TString fname)
  {
    /** embed into **/

    /** check if a file is already open **/
    if (mEmbedFile && mEmbedFile->IsOpen()) {
      LOG(ERROR) << "Another embedding file is currently open" << std::endl;
      return kFALSE;
    }
    
    /** open file **/
    mEmbedFile = TFile::Open(fname);
    if (!mEmbedFile || !mEmbedFile->IsOpen()) {
      LOG(ERROR) << "Cannot open file for embedding: " << fname << std::endl;
      return kFALSE;
    }

    /** get tree **/
    mEmbedTree = (TTree *)mEmbedFile->Get("o2sim");
    if (!mEmbedTree) { 
      LOG(ERROR) << "Cannot find \"o2sim\" tree for embedding in " << fname << std::endl;
      return kFALSE;
   }

    /** get entries **/
    mEmbedEntries = mEmbedTree->GetEntries();
    if (mEmbedEntries <= 0) {
      LOG(ERROR) << "Invalid number of entries found in tree for embedding: " << mEmbedEntries << std::endl;
      return kFALSE;
    }

    /** connect MC event header **/
    TBranch *theBranch = mEmbedTree->GetBranch("MCEventHeader.");
    TClass *theClass = new TClass();
    EDataType theType;
    theBranch->GetExpectedType(theClass, theType);
    mEmbedEvent = (FairMCEventHeader *)theClass->New();
    mEmbedTree->SetBranchAddress("MCEventHeader.", &mEmbedEvent);
    
    /** success **/
    return kTRUE;
  }
  
  /*****************************************************************/
  /*****************************************************************/  
   
} /* namespace eventgen */
} /* namespace o2 */

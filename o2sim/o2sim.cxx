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

#include "FairRunSim.h"
#include "Core/RunManager.h"

int
main (Int_t argc, char **argv)
{

  FairRunSim *rs = new FairRunSim();
  o2sim::RunManager *rm = new o2sim::RunManager();

  if (argc == 2) if (!rm->ProcessFile(argv[1])) exit(1);
  if (!rm->Init()) exit(1);
  if (!rm->Run()) exit(1);
  if (!rm->Terminate()) exit(1);

  delete rm;
  delete rs;
  
  return 0;
}

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

#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include "FairRunSim.h"
#include "Run/RunManager.h"

int
main (Int_t argc, char **argv)
{

  /** create instances **/
  FairRunSim *rs = new FairRunSim();
  o2sim::RunManager *rm = new o2sim::RunManager();

  /** process arguments **/
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help", "Print help messages")
    ("engine", po::value<std::string>(), "The simulation engine")
    ("generator", po::value<std::string>(), "Select a generator recipe")
    ("nevents", po::value<int>(), "Number of events to be generated")
    ("config", po::value<std::string>(), "Use custom configuration from file")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  /** command buffer **/
  std::vector<std::string> commandBuffer;
  
  /** process custom configuration file **/
  if (vm.count("config")) {
    std::string customcfg = vm["config"].as<std::string>();
    std::cout << "Using custom configuration: " << customcfg << std::endl;
    commandBuffer.push_back("include() " + customcfg);
  }
  /** process default configuration file **/
  else {
    commandBuffer.push_back("include() $O2SIM_ROOT/receipes/o2sim.cfg");
  }

  if (vm.count("engine")) {
    std::string engine = vm["engine"].as<std::string>();
    commandBuffer.push_back("simulation.mc_engine " + engine);
  }

  if (vm.count("generator")) {
    std::string generatorcfg = vm["generator"].as<std::string>();
    std::cout << "Using generator receipe: " << generatorcfg << std::endl;
    generatorcfg = "$O2SIM_ROOT/receipes/generators/" + generatorcfg + ".cfg";
    commandBuffer.push_back("generator.include() " + generatorcfg);
  }

  if (vm.count("nevents")) {
    int nevents = vm["nevents"].as<int>();
    std::stringstream command;
    command << "simulation.nevents " << nevents;
    commandBuffer.push_back(command.str());
  }

  /** process command buffer **/
  if (!rm->ProcessBuffer(commandBuffer)) exit(1);
  /** init **/
  if (!rm->Init()) exit(1);
  /** run **/
  if (!rm->Run()) exit(1);
  /** terminate **/
  if (!rm->Terminate()) exit(1);

  delete rm;
  delete rs;
  
  return 0;
}

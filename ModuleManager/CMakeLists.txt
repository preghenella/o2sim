# @author R+Preghenella - August 2017

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(o2sim)

set(MODULE o2simModuleManager)

set(SOURCES
    ModuleManager.cxx
    ModuleManagerDelegate.cxx
    ModuleManagerCave.cxx
    ModuleManagerTPC.cxx
    )
   
set(HEADERS
    ModuleManager.h
    ModuleManagerDelegate.h
    ModuleManagerCave.h
    ModuleManagerTPC.h
    )

O2SIM_GENERATE_LIBRARY()


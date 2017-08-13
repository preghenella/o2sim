# @author R+Preghenella - August 2017

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(o2sim)

set(MODULE o2simSimulationManager)

set(SOURCES
    SimulationManager.cxx
    )
   
set(HEADERS
    SimulationManager.h
    )

O2SIM_GENERATE_LIBRARY()

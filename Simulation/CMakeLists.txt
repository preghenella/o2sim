# @author R+Preghenella - August 2017

set(MODULE ro2simSimulation)

set(MODULE_DEPENDENCIES ro2simCore)

set(SOURCES
    SimulationManager.cxx
    )
   
set(HEADERS
    SimulationManager.h
    )

O2SIM_GENERATE_LIBRARY()

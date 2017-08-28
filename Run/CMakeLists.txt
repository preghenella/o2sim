# @author R+Preghenella - August 2017

set(MODULE ro2simRun)

set(MODULE_DEPENDENCIES ro2simCore ro2simSimulation ro2simModule ro2simGenerator)

set(SOURCES
    RunManager.cxx
    )
   
set(HEADERS
    RunManager.h
    )

O2SIM_GENERATE_LIBRARY()


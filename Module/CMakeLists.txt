# @author R+Preghenella - August 2017

set(MODULE ro2simModule)

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


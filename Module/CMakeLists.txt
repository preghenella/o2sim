# @author R+Preghenella - August 2017

set(MODULE ro2simModule)

set(MODULE_DEPENDENCIES ro2simCore)

set(SOURCES
    ModuleManager.cxx
    ModuleManagerCave.cxx
    ModuleManagerTPC.cxx
    )
   
set(HEADERS
    ModuleManager.h
    ModuleManagerCave.h
    ModuleManagerTPC.h
    )

O2SIM_GENERATE_LIBRARY()


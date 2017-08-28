# @author R+Preghenella - August 2017

set(MODULE ro2simCore)

set(SOURCES
    ConfigurationManager.cxx
    ModuleManagerDelegate.cxx
    GeneratorManagerDelegate.cxx
    TriggerManagerDelegate.cxx
    RunManagerDelegate.h
    )
   
set(HEADERS
    ConfigurationManager.h
    ModuleManagerDelegate.h
    GeneratorManagerDelegate.h
    TriggerManagerDelegate.h
    RunManagerDelegate.cxx
    )
		    
O2SIM_GENERATE_LIBRARY()

# @author R+Preghenella - August 2017

set(MODULE o2simGeneratorManager)

set(SOURCES
    GeneratorManager.cxx
    GeneratorManagerDelegate.cxx
    GeneratorManagerPythia6.cxx
    )
   
set(HEADERS
    GeneratorManager.h
    GeneratorManagerDelegate.h
    GeneratorManagerPythia6.h
    )
		    
O2SIM_GENERATE_LIBRARY()

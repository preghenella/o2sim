# @author R+Preghenella - August 2017

set(MODULE o2simGeneratorManager)

include_directories($ENV{HOME}/alice/AEGIS/THijing)

set(SOURCES
    GeneratorManager.cxx
    GeneratorManagerDelegate.cxx
    GeneratorManagerBox.cxx
    GeneratorManagerPythia6.cxx
    GeneratorManagerHijing.cxx
    )
   
set(HEADERS
    GeneratorManager.h
    GeneratorManagerDelegate.h
    GeneratorManagerBox.h
    GeneratorManagerPythia6.h
    GeneratorManagerHijing.h
    )
		    
O2SIM_GENERATE_LIBRARY()

# @author R+Preghenella - August 2017

set(MODULE o2simGeneratorManager)

include_directories($ENV{HOME}/alice/AEGIS/THijing
		    $ENV{HEPMC3_ROOT}/include)

set(SOURCES
    GeneratorManager.cxx
    GeneratorManagerDelegate.cxx
    GeneratorManagerBox.cxx
    GeneratorManagerPythia6.cxx
    GeneratorManagerHijing.cxx
    GeneratorHepMC.cxx
    )
   
set(HEADERS
    GeneratorManager.h
    GeneratorManagerDelegate.h
    GeneratorManagerBox.h
    GeneratorManagerPythia6.h
    GeneratorManagerHijing.h
    GeneratorHepMC.h
    )
		    
O2SIM_GENERATE_LIBRARY()

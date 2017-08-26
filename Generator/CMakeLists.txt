# @author R+Preghenella - August 2017

set(MODULE ro2simGenerator)

include_directories($ENV{HOME}/alice/AEGIS/THijing
		    $ENV{HEPMC3_ROOT}/include)

set(SOURCES
    Generator.cxx
    GeneratorHepMC.cxx
    GeneratorManager.cxx
    GeneratorManagerDelegate.cxx
    GeneratorManagerBox.cxx
    GeneratorManagerPythia.cxx
    GeneratorManagerHijing.cxx
    )
   
set(HEADERS
    Generator.h
    GeneratorHepMC.h
    GeneratorManager.h
    GeneratorManagerDelegate.h
    GeneratorManagerBox.h
    GeneratorManagerPythia.h
    GeneratorManagerHijing.h
    )
		    
O2SIM_GENERATE_LIBRARY()

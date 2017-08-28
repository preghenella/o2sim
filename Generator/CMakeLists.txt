# @author R+Preghenella - August 2017

set(MODULE ro2simGenerator)

set(MODULE_DEPENDENCIES ro2simCore ro2simTrigger)

include_directories($ENV{HOME}/alice/AEGIS/THijing
		    $ENV{HEPMC3_ROOT}/include)

set(SOURCES
    MCEventHeader.cxx
    PrimaryGenerator.cxx
    Generator.cxx
    GeneratorHepMC.cxx
    GeneratorManager.cxx
    GeneratorManagerBox.cxx
    GeneratorManagerPythia.cxx
    GeneratorManagerHijing.cxx
    )
   
set(HEADERS
    MCEventHeader.h
    PrimaryGenerator.h
    Generator.h
    GeneratorHepMC.h
    GeneratorManager.h
    GeneratorManagerBox.h
    GeneratorManagerPythia.h
    GeneratorManagerHijing.h
    )
		    
O2SIM_GENERATE_LIBRARY()

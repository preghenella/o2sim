# @author R+Preghenella - August 2017

set(MODULE ro2simGenerator)

find_library(HEPMC3_LIBRARY NAMES HepMC HINTS "$ENV{HEPMC3_ROOT}/lib")
set(MODULE_DEPENDENCIES ro2simCore ro2simTrigger ${HEPMC3_LIBRARY} THijing)

include_directories($ENV{HOME}/alice/AEGIS/THijing
		    $ENV{HEPMC3_ROOT}/include)

set(SOURCES
    MCEventHeader.cxx
    PrimaryGenerator.cxx
    Generator.cxx
    GeneratorHeader.cxx
    GeneratorInfo.cxx
    CrossSectionInfo.cxx
    HeavyIonInfo.cxx
    GeneratorHepMC.cxx
    GeneratorTGenerator.cxx
    GeneratorManager.cxx
    GeneratorManagerBox.cxx
    GeneratorManagerPythia.cxx
    GeneratorManagerHijing.cxx
    )
   
set(HEADERS
    MCEventHeader.h
    PrimaryGenerator.h
    Generator.h
    GeneratorHeader.h
    GeneratorInfo.h
    CrossSectionInfo.h
    HeavyIonInfo.h
    GeneratorHepMC.h
    GeneratorTGenerator.h
    GeneratorManager.h
    GeneratorManagerBox.h
    GeneratorManagerPythia.h
    GeneratorManagerHijing.h
    )
		    
O2SIM_GENERATE_LIBRARY()

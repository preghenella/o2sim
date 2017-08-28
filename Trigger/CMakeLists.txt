# @author R+Preghenella - August 2017

set(MODULE ro2simTrigger)

set(MODULE_DEPENDENCIES ro2simCore)

include_directories($ENV{HEPMC3_ROOT}/include)

set(SOURCES 
    Trigger.cxx
    TriggerHepMC.cxx
    TriggerTGenerator.cxx
    ParticleTrigger.cxx
    TriggerManagerParticle.cxx
   )
   
set(HEADERS
    Trigger.h
    TriggerHepMC.h
    TriggerTGenerator.h
    ParticleTrigger.h
    TriggerManagerParticle.h
    )
		    
O2SIM_GENERATE_LIBRARY()

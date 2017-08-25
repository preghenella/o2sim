# @author R+Preghenella - August 2017

set(MODULE o2simTrigger)

include_directories($ENV{HEPMC3_ROOT}/include)

set(SOURCES 
    Trigger.cxx
    TriggerHepMC.cxx
    TriggerTGenerator.cxx
    ParticleTrigger.cxx
    TriggerManagerDelegate.cxx
    TriggerManagerParticle.cxx
   )
   
set(HEADERS
    Trigger.h
    TriggerHepMC.h
    TriggerTGenerator.h
    ParticleTrigger.h
    TriggerManagerDelegate.h
    TriggerManagerParticle.h
    )
		    
O2SIM_GENERATE_LIBRARY()

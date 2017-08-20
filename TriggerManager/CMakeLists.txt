# @author R+Preghenella - August 2017

set(MODULE o2simTriggerManager)

include_directories($ENV{HEPMC3_ROOT}/include)

set(SOURCES 
    Trigger.cxx
    ParticleTrigger.cxx
    TriggerManagerDelegate.cxx
    TriggerManagerParticle.cxx
   )
   
set(HEADERS
    Trigger.h
    ParticleTrigger.h
    TriggerManagerDelegate.h
    TriggerManagerParticle.h
    )
		    
O2SIM_GENERATE_LIBRARY()

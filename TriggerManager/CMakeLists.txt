# @author R+Preghenella - August 2017

set(MODULE o2simTriggerManager)

set(SOURCES 
    TriggerManagerDelegate.cxx
    TriggerManagerParticle.cxx
   )
   
set(HEADERS
    TriggerManagerDelegate.h
    TriggerManagerParticle.h
    )
		    
O2SIM_GENERATE_LIBRARY()

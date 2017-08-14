# @author R+Preghenella - August 2017

set(MODULE o2simCore)

set(SOURCES
    ConfigurationManager.cxx
    RunManager.cxx
    RunManagerDelegate.cxx
    )
   
set(HEADERS
    ConfigurationManager.h
    RunManager.h
    RunManagerDelegate.h
    )
		    
O2SIM_GENERATE_LIBRARY()

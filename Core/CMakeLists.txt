# @author R+Preghenella - August 2017

set(MODULE o2simCore)

set(SOURCES
    ConfigurationManager.cxx
    RunManager.cxx
    )
   
set(HEADERS
    ConfigurationManager.h
    RunManager.h
    )
		    
O2SIM_GENERATE_LIBRARY()

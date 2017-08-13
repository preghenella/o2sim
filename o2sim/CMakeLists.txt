# @author R+Preghenella - August 2017

set(SOURCES
    o2sim.cxx
    )
   
add_executable(o2sim ${SOURCES})
target_link_libraries(o2sim
		      o2simCore
		      o2simSimulationManager
		      o2simModuleManager
		      o2simGeneratorManager
		      )

install(TARGETS o2sim RUNTIME DESTINATION bin)


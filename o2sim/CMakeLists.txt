# @author R+Preghenella - August 2017

set(SOURCES
    o2sim.cxx
    )

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(o2sim ${SOURCES})
target_link_libraries(o2sim
		      o2simCore
		      o2simSimulation
		      o2simModule
		      o2simGenerator
		      o2simTrigger
		      ${Boost_PROGRAM_OPTIONS_LIBRARY}
		      )

install(TARGETS o2sim RUNTIME DESTINATION bin)


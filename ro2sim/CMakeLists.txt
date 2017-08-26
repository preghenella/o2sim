# @author R+Preghenella - August 2017

set(SOURCES
    ro2sim.cxx
    )

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ro2sim ${SOURCES})
target_link_libraries(ro2sim
		      ro2simCore
		      ro2simSimulation
		      ro2simModule
		      ro2simGenerator
		      ro2simTrigger
		      ${Boost_PROGRAM_OPTIONS_LIBRARY}
		      )

install(TARGETS ro2sim RUNTIME DESTINATION bin)


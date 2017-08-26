# @author R+Preghenella - August 2017

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(ro2sim)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS EGPythia6)
include(${ROOT_USE_FILE})
include(O2SimUtils)

include_directories(
		    ${CMAKE_CURRENT_SOURCE_DIR}/.
		    $ENV{FAIRROOT_ROOT}/include
		    $ENV{O2_ROOT}/include
		    )

link_directories(
		 $ENV{FAIRROOT_ROOT}/lib
		 $ENV{O2_ROOT}/lib
		 $ENV{HEPMC3_ROOT}/lib
		 )

add_subdirectory(Core)
add_subdirectory(Simulation)
add_subdirectory(Module)
add_subdirectory(Generator)
add_subdirectory(Trigger)
add_subdirectory(ro2sim)

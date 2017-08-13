# @author R+Preghenella - August 2017

################################################################################
# O2SIM_GENERATE_LIBRARY
################################################################################

macro(O2SIM_GENERATE_LIBRARY)

  ROOT_GENERATE_DICTIONARY(G__${MODULE} ${HEADERS} LINKDEF ${MODULE}_LinkDef.h)
  add_library(${MODULE} SHARED ${SOURCES} G__${MODULE}.cxx)
  target_link_libraries(${MODULE} ${ROOT_LIBRARIES} Base DetectorsPassive TPCSimulation)
  install(TARGETS ${MODULE} LIBRARY DESTINATION lib)

  if (${ROOT_VERSION} VERSION_GREATER "6.0")
     install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${MODULE}_rdict.pcm ${CMAKE_CURRENT_BINARY_DIR}/lib${MODULE}.rootmap DESTINATION lib)
  endif (${ROOT_VERSION} VERSION_GREATER "6.0")

  if(${CMAKE_SYSTEM} MATCHES Darwin)
     set_target_properties(${MODULE} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  endif(${CMAKE_SYSTEM} MATCHES Darwin)

endmacro(O2SIM_GENERATE_LIBRARY)


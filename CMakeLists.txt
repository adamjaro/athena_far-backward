
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
cmake_policy(SET CMP0074 NEW)

project(athena_far-backward)

SET(CMAKE_CXX_STANDARD 17)

find_package( DD4hep REQUIRED )
include( ${DD4hep_DIR}/cmake/DD4hep.cmake )
include( ${DD4hep_DIR}/cmake/DD4hepBuild.cmake )
dd4hep_configure_output()

dd4hep_set_compiler_flags()

dd4hep_add_plugin(athena_far-backward SOURCES src/*.cpp
  USES DD4hep::DDCore DD4hep::DDG4
  )

install(TARGETS athena_far-backward LIBRARY DESTINATION lib)


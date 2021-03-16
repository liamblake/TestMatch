cmake_minimum_required(VERSION 3.0)
#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

project(testmatch_backend)

# Boost variables, dependent upon os
#set(Boost_DEBUG 1)
#set(Boost_COMPILER "-vc142")
#SET(BOOST_ROOT "D:/boost/boost_1_76_0")
#SET(Boost_INCLUDE_DIR "D:/boost/boost_1_76_0")
#SET(BOOST_LIBRARYDIR "D:/boost/boost_1_76_0/stage/lib")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

###############################################################################
## file globbing ##############################################################
###############################################################################

set(sources src/Cards.cpp src/FileIO.cpp src/Player.cpp src/Simulation.cpp include/Cards.h include/FileIO.h include/Player.h include/Simulation.h include/Utility.h)
set(includes include/Cards.h include/FileIO.h include/Player.h include/Simulation.h include/Utility.h)
file(GLOB sources_unittests test/unit/*.cpp)

file(GLOB sources_demo test/*.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_library(backend ${sources})

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(backend PUBLIC include)

###############################################################################
## dependencies ###############################################################
###############################################################################


#set(BOOST_ROOT boost)
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.72.0 COMPONENTS unit_test_framework serialization REQUIRED)

include_directories(backend ${Boost_INCLUDE_DIR}})
target_link_libraries(backend PUBLIC
  ${Boost_LIBRARIES}
)

###############################################################################
## testing ####################################################################
###############################################################################

# Demonstrative test (for run-time errors)
#add_executable(demo_test ${sources_demo})
#target_include_directories(demo_test PUBLIC include)
#include_directories(demo_test ${Boost_INCLUDE_DIR})
#target_link_libraries(demo_test PUBLIC
#  ${Boost_LIBRARIES}
#  backend
#)


# Unit tests
add_executable(unit_tests WIN32 ${sources_unittests})

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_include_directories(unit_tests PUBLIC include)
include_directories(unit_tests ${Boost_INCLUDE_DIR})
target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
  backend
)

set_target_properties(unit_tests PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)

#add_link_options(unit_tests "-mwindows")
enable_testing()
add_test(UnitTests unit_tests)

cmake_minimum_required(VERSION 3.0)
#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

project(testmatch_backend)
include(CTest)
# Boost variables, dependent upon os
#set(Boost_DEBUG 1)
#set(Boost_COMPILER "-vc142")
#SET(BOOST_ROOT "D:/boost/boost_1_76_0")
#SET(Boost_INCLUDE_DIR "D:/boost/boost_1_76_0")
#SET(BOOST_LIBRARYDIR "D:/boost/boost_1_76_0/stage/lib")

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

###############################################################################
## file globbing ##############################################################
###############################################################################

set(sources src/Cards.cpp src/FileIO.cpp src/Player.cpp src/Simulation.cpp include/Cards.h include/FileIO.h include/Player.h include/Simulation.h include/Utility.h include/MatchTime.h)
set(includes include/Cards.h include/FileIO.h include/Player.h include/Simulation.h include/Utility.h include/MatchTime.h)

# Automatically add all tests
file(GLOB sources_unittests test/unit/*.cpp)
file(GLOB sources_demo test/*.cpp)

###############################################################################
## dependencies ###############################################################
###############################################################################


#set(BOOST_ROOT boost)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.70.0 COMPONENTS unit_test_framework serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_library(backend ${sources})

target_include_directories(backend PUBLIC include)

target_include_directories(backend PUBLIC ${Boost_INCLUDE_DIR}})
target_link_libraries(backend PUBLIC
  ${Boost_LIBRARIES}
)

set_target_properties(backend PROPERTIES LINK_FLAGS /FORCE:MULTIPLE)

###############################################################################
## testing ####################################################################
###############################################################################
add_subdirectory(test)



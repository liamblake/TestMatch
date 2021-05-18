cmake_minimum_required(VERSION 3.1)
project(testmatch_backend)
include(CTest)
include(GenerateExportHeader)

# Ensure C++20 is used
set(CMAKE_CXX_STANDARD 20)

# Build options
option(BUILD_TESTS "Option to also compile testing executables" ON)

# Compiler flags
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Sources
set(sources src/cards.cpp src/fileio.cpp src/team.cpp src/models.cpp src/simulation.cpp src/helpers.cpp src/enums.cpp src/matchtime.cpp src/pregame.cpp)
set(includes include/cards.hpp include/fileio.hpp include/team.hpp include/models.hpp include/simulation.hpp include/helpers.hpp include/matchtime.h include/enums.cpp)

# Automatically add all tests
file(GLOB sources_unittests test/unit/*.cpp)
file(GLOB sources_demo test/*.cpp)

# Boost dependency
#add_definitions( -DBOOST_ALL_NO_LIB )
#add_definitions( -DBOOST_ALL_DYN_LINK )
find_package(Boost 1.70.0 COMPONENTS unit_test_framework serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add data to target
add_library(TestMatch ${sources})
#target_sources(TestMatch PUBLIC ${includes})
target_include_directories(TestMatch PUBLIC include include/testmatch)
target_include_directories(TestMatch PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(TestMatch PUBLIC
  ${Boost_LIBRARIES}
)

# Generate macros for exporting functions 
generate_export_header(TestMatch)
target_include_directories(TestMatch PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

install(PROGRAMS ${Boost_LIBRARIES} DESTINATION ${PROJECT_BINARY_DIR})


# OPTIONAL: Build tests:
if (BUILD_TESTS)
  # Link fixtures
  target_include_directories(TestMatch PUBLIC test/unit)
	add_subdirectory(test)
  enable_testing()
endif()


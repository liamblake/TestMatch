cmake_minimum_required(VERSION 3.0)
project(testmatch_backend)
include(CTest)
include(GenerateExportHeader)

# Build options
option(BUILD_TESTS "Option to also compile testing executables" ON)

# Compiler flags
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Sources
set(sources src/Cards.cpp src/FileIO.cpp src/Player.cpp src/Model.cpp src/Simulation.cpp src/MatchTime.cpp include/Cards.h include/FileIO.h include/Player.h include/Model.h include/Simulation.h include/Utility.h include/MatchTime.h)
set(includes include/Cards.h include/FileIO.h include/Player.h include/Model.h include/Simulation.h include/Utility.h include/MatchTime.h)

# Automatically add all tests
file(GLOB sources_unittests test/unit/*.cpp)
file(GLOB sources_demo test/*.cpp)

# Boost dependency
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.70.0 COMPONENTS unit_test_framework serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add data to target
add_library(TestMatch ${sources})
target_include_directories(TestMatch PUBLIC include)
target_include_directories(TestMatch PUBLIC ${Boost_INCLUDE_DIR}})
target_link_libraries(TestMatch PUBLIC
  ${Boost_LIBRARIES}
)


# Generate macros for exporting functions 
generate_export_header(backend)
target_include_directories(backend PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})


# OPTIONAL: Build tests:
if (BUILD_TESTS)
	add_subdirectory(test)
endif()


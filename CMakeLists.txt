cmake_minimum_required(VERSION 3.1)
project(testmatch_backend)
include(CTest)
include(GenerateExportHeader)

# Ensure C++20 is used
set(CMAKE_CXX_STANDARD 20)

# Build options
option(BUILD_PYTHON "Option to also compile Python bindings (requires Boost.Python)" OFF)
option(BUILD_TESTS "Option to also compile testing executables (requires Boost.UnitTestFramework" OFF)

# Compiler flags
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Sources
set(sources 
  src/cpp/cards.cpp 
  src/cpp/team.cpp 
  src/cpp/models.cpp 
  src/cpp/simulation.cpp 
  src/cpp/helpers.cpp 
  src/cpp/enums.cpp 
  src/cpp/matchtime.cpp 
  src/cpp/pregame.cpp
)

# Boost dependency
find_package(Boost 1.70.0 COMPONENTS unit_test_framework REQUIRED)
include_directories(
  ${Boost_INCLUDE_DIR} 
  ${CMAKE_SOURCE_DIR}/include
)

# Add data to target
add_library(TestMatch ${sources})
target_include_directories(TestMatch PUBLIC ${CMAKE_SOURCE_DIR}/include/testmatch)
target_include_directories(TestMatch PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(TestMatch PUBLIC
  ${Boost_LIBRARIES}
)

# 
install(TARGETS TestMatch DESTINATION bin)

# OPTIONAL: Build Python wrapper
if (BUILD_PYTHON)
  add_subdirectory(src/cpp/bindings)
endif()

# OPTIONAL: Build tests
if (BUILD_TESTS)
	add_subdirectory(test/cpp)
  enable_testing()
endif()


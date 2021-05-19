# Include directory
include_directories(include)

# Compile example simulation
#add_executable(demo demonstrative_test.cpp)

#target_link_libraries(demo PUBLIC
#  ${Boost_LIBRARIES}
#  TestMatch
#)

# Register as test
#add_test(NAME demo COMMAND demo)

# Unit tests
# Automatically add all tests
file(GLOB sources_unittests unit/*.cpp)
file(GLOB headers_unittests unit/*.hpp)

add_executable(unit_tests ${sources_unittests})

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_include_directories(unit_tests PUBLIC
    include 
    ${Boost_INCLUDE_DIR}
    headers_unittests
)

target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
  TestMatch
)

add_test(NAME unit COMMAND unit_tests)
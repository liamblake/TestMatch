# Unit tests
# Automatically add all tests
file(GLOB sources_unittests unit/*.cpp)
file(GLOB headers_unittests unit/*.hpp)

add_executable(unit_tests ${sources_unittests})

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_include_directories(unit_tests PUBLIC
    include ${Boost_INCLUDE_DIR}
    headers_unittests
)

target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
  TestMatch
)

add_test(NAME unit COMMAND unit_tests)
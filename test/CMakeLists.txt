# Unit tests
add_executable(unit_tests ${sources_unittests})

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_include_directories(unit_tests PUBLIC include)
target_include_directories(unit_tests PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
  TestMatch
)

add_test(NAME unit COMMAND unit_tests)
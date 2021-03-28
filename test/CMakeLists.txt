# Demonstrative test (for run-time errors)
add_executable(demo_test ${sources_demo})

target_include_directories(demo_test PUBLIC includes)
include_directories(demo_test ${Boost_INCLUDE_DIR})
target_link_libraries(demo_test PUBLIC
  ${Boost_LIBRARIES}
  backend
)

#set_target_properties(demo_test PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
#add_test(NAME demo COMMAND demo_test)

# Unit tests
add_executable(unit_tests ${sources_unittests})

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_include_directories(unit_tests PUBLIC includes)
include_directories(unit_tests ${Boost_INCLUDE_DIR})
target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
  backend
)


IF (WIN32)
  #set_target_properties(demo_test PROPERTIES LINK_FLAGS /FORCE:MULTIPLE)
  #set_target_properties(unit_tests PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
  #set_target_properties(unit_tests PROPERTIES LINK_FLAGS /FORCE:MULTIPLE)
ENDIF()

add_test(NAME unit COMMAND unit_tests)
enable_testing()
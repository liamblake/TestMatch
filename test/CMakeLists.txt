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
#set_target_properties(unit_tests PROPERTIES 
#  IMPORTED_LOCATION ${Boost_LIBRARYDIR}/liblept168.dll
#)

target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_include_directories(unit_tests PUBLIC
    ${CMAKE_SOURCE_DIR}/include 
    ${Boost_INCLUDE_DIR}
    headers_unittests
)

target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
  TestMatch
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(NAME unit COMMAND unit_tests)

# Install UTF libraries
get_filename_component(UTF_BASE_NAME ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} NAME_WE)
get_filename_component(UTF_PATH ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} PATH)
install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
  DESTINATION .
  #CONFIGURATIONS Release RelWithDebInfo
)

get_filename_component(UTF_BASE_NAME_DEBUG ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_DEBUG} NAME_WE)
install(FILES ${UTF_PATH}/${UTF_BASE_NAME_DEBUG}.dll
  DESTINATION .
  #CONFIGURATIONS Debug
)
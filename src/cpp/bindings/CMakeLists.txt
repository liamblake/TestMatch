if(SKBUILD)
  # Scikit-Build does not add your site-packages to the search path automatically,
  # so we need to add it _or_ the pybind11 specific directory here.
  execute_process(
    COMMAND
      "${PYTHON_EXECUTABLE}" -c
      "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE _tmp_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT)
  list(APPEND CMAKE_PREFIX_PATH "${_tmp_dir}")
endif()

FIND_PACKAGE(pybind11 CONFIG REQUIRED)
pybind11_add_module(_testmatch MODULE wrappers.cpp)

target_link_libraries(_testmatch
        TestMatch
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
)

target_include_directories(_testmatch PUBLIC
    ${CMAKE_SOURCE_DIR}/include 
    ${Boost_INCLUDE_DIR}
)
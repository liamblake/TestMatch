# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TestMatchGui_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TestMatchGui_autogen.dir\\ParseCache.txt"
  "TestMatchGui_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\mouseEvent_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\mouseEvent_autogen.dir\\ParseCache.txt"
  "mouseEvent_autogen"
  )
endif()

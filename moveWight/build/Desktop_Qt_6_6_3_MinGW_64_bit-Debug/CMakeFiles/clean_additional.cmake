# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\moveWight_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\moveWight_autogen.dir\\ParseCache.txt"
  "moveWight_autogen"
  )
endif()

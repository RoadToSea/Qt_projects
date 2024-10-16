# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Serial_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Serial_autogen.dir\\ParseCache.txt"
  "Serial_autogen"
  )
endif()

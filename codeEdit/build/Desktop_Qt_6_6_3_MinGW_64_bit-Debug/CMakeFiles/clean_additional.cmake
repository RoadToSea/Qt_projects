# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\codeEdit_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\codeEdit_autogen.dir\\ParseCache.txt"
  "codeEdit_autogen"
  )
endif()

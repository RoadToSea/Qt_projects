# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\album_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\album_autogen.dir\\ParseCache.txt"
  "album_autogen"
  )
endif()

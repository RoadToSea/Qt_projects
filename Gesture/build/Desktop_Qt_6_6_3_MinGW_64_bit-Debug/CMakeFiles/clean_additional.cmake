# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Gesture_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Gesture_autogen.dir\\ParseCache.txt"
  "Gesture_autogen"
  )
endif()

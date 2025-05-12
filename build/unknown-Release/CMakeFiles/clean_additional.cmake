# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/DebateTimer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DebateTimer_autogen.dir/ParseCache.txt"
  "DebateTimer_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appPlayoff_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appPlayoff_autogen.dir/ParseCache.txt"
  "appPlayoff_autogen"
  )
endif()

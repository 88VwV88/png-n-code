# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.30
cmake_policy(SET CMP0009 NEW)

# SOURCES at CMakeLists.txt:7 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/code/c-cpp/PNGnCode/src//*.c")
set(OLD_GLOB
  "D:/code/c-cpp/PNGnCode/src//PNGdCoder.c"
  "D:/code/c-cpp/PNGnCode/src//lodepng.c"
  "D:/code/c-cpp/PNGnCode/src//main.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/code/c-cpp/PNGnCode/build/CMakeFiles/cmake.verify_globs")
endif()
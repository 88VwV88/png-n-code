cmake_minimum_required(VERSION 3.10)
project(PNGnCode VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CURRENT_SOURCE_DIR "src/")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(gcc_like_c "$<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_c "$<COMPILE_LANG_AND_ID:C,MSVC>")
add_library(compiler_flags INTERFACE)

target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_c}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
  "$<${msvc_c}:-W3>"
)
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_c}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_c}:$<BUILD_INTERFACE:-W3>>"
)

add_executable(PNGnCode "${SOURCES}")

target_include_directories(PNGnCode PUBLIC "include/")
target_link_libraries(PNGnCode z compiler_flags)
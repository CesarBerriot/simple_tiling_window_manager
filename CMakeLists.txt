cmake_minimum_required(VERSION 3.27)
project(simple_tiling_window_manager C)

add_compile_options(-ansi -pedantic-errors -std=c11 -Wall -Wextra)

set(CMAKE_C_STANDARD 11)

add_library(dll SHARED dll.c)
set_target_properties(dll PROPERTIES OUTPUT_NAME hook_dll PREFIX "")

add_executable(simple_tiling_window_manager main.c)
target_link_libraries(simple_tiling_window_manager PRIVATE dll)

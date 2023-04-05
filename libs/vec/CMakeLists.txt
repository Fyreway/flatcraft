cmake_minimum_required(VERSION 3.26)
project(vec LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(VEC_SOURCES src/vec.c)

add_library(vec STATIC ${VEC_SOURCES})

target_include_directories(vec PRIVATE include)

set_target_properties(vec PROPERTIES PUBLIC_HEADER include/vec/vec.h)

cmake_minimum_required(VERSION 3.26)
project(flatcraft LANGUAGES C)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(libs/vec)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(FLATCRAFT_SOURCES src/main.c src/util.c src/state.c src/render.c src/event.c src/block.c src/chunk.c)

add_executable(flatcraft ${FLATCRAFT_SOURCES})

target_include_directories(flatcraft PRIVATE src PUBLIC ${SDL2_INCLUDE_DIRS} libs/vec/include)

target_link_libraries(flatcraft PUBLIC SDL2 SDL2_image vec)

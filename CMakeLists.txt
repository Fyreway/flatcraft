cmake_minimum_required(VERSION 3.26)
project(flatcraft LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FLATCRAFT_SOURCES src/main.cpp src/util.cpp src/state.cpp src/render.cpp src/event.cpp src/block.cpp src/chunk.cpp src/player.cpp)

add_executable(flatcraft ${FLATCRAFT_SOURCES})

target_include_directories(flatcraft PRIVATE src PUBLIC ${SDL2_INCLUDE_DIRS})

target_link_libraries(flatcraft PUBLIC SDL2 SDL2_image)

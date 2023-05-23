cmake_minimum_required(VERSION 3.26)
project(flatcraft LANGUAGES CXX)
project(SimplexNoise)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FLATCRAFT_SOURCES src/main.cpp src/util.cpp src/state.cpp src/render.cpp src/event.cpp src/block.cpp src/chunk.cpp src/player.cpp)
set(SIMPLEXNOISE_SOURCES SimplexNoise/src/SimplexNoise.cpp)

add_executable(flatcraft ${FLATCRAFT_SOURCES})

add_library(SimplexNoise ${SIMPLEXNOISE_SOURCES})

target_include_directories(flatcraft PRIVATE src PUBLIC ${SDL2_INCLUDE_DIRS} SimplexNoise/src)

target_link_libraries(flatcraft PUBLIC SDL2 SDL2_image SDL2_ttf SimplexNoise)

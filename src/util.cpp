#include "util.hpp"

#include <iostream>

#include <SDL.h>

void util::error_sdl(const std::string &proc) {
    std::cerr << "SDL Error occurred during " << proc << ": " << SDL_GetError()
              << std::endl;
    exit(1);
}

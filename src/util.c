#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

void error_sdl(const char *proc) {
    fprintf(stderr, "SDL Error occurred during %s: %s\n", proc, SDL_GetError());
    exit(1);
}

#include "state.h"
#include <SDL_video.h>

#include "util.h"

SdlState init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) error_sdl("initialization");

    SDL_Window *win = SDL_CreateWindow("flatcraft",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800,
                                       600,
                                       0);
    if (win == NULL) error_sdl("window creation");

    SDL_Renderer *rend = SDL_CreateRenderer(
        win,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (rend == NULL) error_sdl("renderer acquisition");

    return (SdlState){.win = win, .rend = rend};
}

void cleanup(SdlState *state) {
    SDL_DestroyWindow(state->win);
    SDL_DestroyRenderer(state->rend);
}

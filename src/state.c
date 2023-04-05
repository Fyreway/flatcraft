#include "state.h"

#include <SDL.h>
#include <SDL_image.h>

#include "util.h"

State init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) error_sdl("SDL init");
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) error_sdl("SDL_image init");

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

    // TODO: normalize path
    SDL_Texture *atlas = IMG_LoadTexture(rend, "../res/terrain.png");

    SdlState sdl_state = {.win = win, .rend = rend, .atlas = atlas};

    Player player = {.x = 0, .y = 0};

    GameState game_state = {.player = player};

    return (State){.sdl_state = sdl_state, .game_state = game_state};
}

void cleanup(State *state) {
    SDL_DestroyTexture(state->sdl_state.atlas);
    SDL_DestroyWindow(state->sdl_state.win);
    SDL_DestroyRenderer(state->sdl_state.rend);

    SDL_Quit();
    IMG_Quit();
}

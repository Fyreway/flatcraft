#include "state.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include "player.hpp"
#include "util.hpp"

flat::State::State() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) util::error_sdl("SDL init");
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        util::error_sdl("SDL_image init");

    win = SDL_CreateWindow("flatcraft",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           WIDTH,
                           HEIGHT,
                           0);
    if (win == nullptr) util::error_sdl("window creation");

    rend = SDL_CreateRenderer(
        win,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (rend == nullptr) util::error_sdl("renderer acquisition");

    // TODO: normalize path
    atlas = IMG_LoadTexture(rend, "../res/terrain.png");
    steve = IMG_LoadTexture(rend, "../res/steve.png");

    for (range(5))
        chunks.insert({i, std::make_unique<Chunk>(Chunk::build_flat(i))});

    player = Player(0.5, 60, chunks);
}

flat::State::~State() {
    SDL_DestroyTexture(atlas);
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);

    SDL_Quit();
    IMG_Quit();
}

void flat::update(State &state) { state.player.update(state.chunks); }

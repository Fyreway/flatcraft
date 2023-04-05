#ifndef __STATE_H__
#define __STATE_H__

#include <SDL.h>
#include <SDL_render.h>
#include <vec/vec.h>

#include "player.h"

typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Texture *atlas;
} SdlState;

typedef struct {
    Player player;
} GameState;

typedef struct {
    SdlState sdl_state;
    GameState game_state;
} State;

State init();

void cleanup(State *state);

#endif

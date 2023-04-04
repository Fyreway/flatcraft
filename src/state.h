#ifndef __STATE_H__
#define __STATE_H__

#include <SDL.h>
#include <SDL_render.h>

typedef struct {
    SDL_Window *win;
    SDL_Renderer *rend;
} SdlState;

SdlState init();

void cleanup(SdlState *state);

#endif

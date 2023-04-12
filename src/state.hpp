#ifndef __STATE_H__
#define __STATE_H__

#include <SDL.h>
#include <SDL_render.h>

#include "player.hpp"

#define WIDTH  800
#define HEIGHT 600

namespace flat {
    class State {
    public:
        Player player;
        std::vector<std::unique_ptr<Chunk>> chunks;

        SDL_Window *win;
        SDL_Renderer *rend;
        SDL_Texture *atlas, *steve;

        State();
        ~State();
    };

    void update(State &state);
}  // namespace flat

#endif

#ifndef __STATE_H__
#define __STATE_H__

#include <memory>
#include <vector>

#include <SDL.h>
#include <SDL_render.h>

#include "chunk.hpp"
#include "player.hpp"

namespace flat {
    class State {
    public:
        Player player;
        std::vector<std::unique_ptr<Chunk>> chunks;

        SDL_Window *win;
        SDL_Renderer *rend;
        SDL_Texture *atlas;

        State();
        ~State();
    };
}  // namespace flat

#endif

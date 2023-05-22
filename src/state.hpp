#ifndef __STATE_H__
#define __STATE_H__

#include <SDL.h>

#include "player.hpp"

#define WIDTH  800
#define HEIGHT 600

namespace flat {
    class State {
    public:
        Player player;
        Chunks chunks;

        SDL_Window *win;
        SDL_Renderer *rend;
        SDL_Texture *atlas, *steve;

        State();
        ~State();

        void handle_events(bool &running);

        void update();

        void render();

    private:
        void render_player();
        void render_block(const Block &block, int chunk_pos);
        void render_block_select();

        void change_block(const Coords &pos,
                          const std::optional<Block::Type> &type);
    };
}  // namespace flat

#endif

#include "render.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include "player.hpp"
#include "util.hpp"

#define SCALE 4

SDL_Rect get_block_texture(flat::Block::Type type) {
    return {(static_cast<int>(type) % 16) * 16,
            (static_cast<int>(type) / 16) * 16,
            16,
            16};
}

SDL_Rect get_block_render_pos(const flat::State &state,
                              const flat::Block &block) {
    return {static_cast<int>(std::round((block.x - state.player.x) * 16 * SCALE)
                             + WIDTH / 2),
            static_cast<int>(std::round((block.y - state.player.y) * 16 * SCALE)
                             + HEIGHT / 2),
            16 * SCALE,
            16 * SCALE};
}

void render_block(flat::State &state, const flat::Block &block) {
    SDL_Rect src = get_block_texture(block.type);
    SDL_Rect dst = get_block_render_pos(state, block);
    SDL_RenderCopy(state.rend, state.atlas, &src, &dst);
}

void render_player(flat::State &state) {
    SDL_Rect steve_src{168, 0, 16 * 8, 32 * 8};
    SDL_Rect steve_dst{WIDTH / 2 - 16 / 2 * SCALE,
                       HEIGHT / 2 - 32 / 2 * SCALE,
                       16 * SCALE,
                       32 * SCALE};
    SDL_RenderCopy(state.rend, state.steve, &steve_src, &steve_dst);
}

void flat::render(flat::State &state) {
    SDL_SetRenderDrawColor(state.rend, 100, 203, 255, 0);
    SDL_RenderClear(state.rend);

    for (std::size_t idx : state.player.near_chunks)
        for (auto const &block : state.chunks.at(idx)->blocks)
            render_block(state, block);

    render_player(state);

    SDL_RenderPresent(state.rend);
}

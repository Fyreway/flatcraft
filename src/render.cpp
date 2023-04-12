#include "render.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include "chunk.hpp"
#include "util.hpp"

#define SCALE 4

SDL_Rect get_block_texture(flat::Block::Type type) {
    return {(static_cast<int>(type) % 16) * 16,
            (static_cast<int>(type) / 16) * 16,
            16,
            16};
}

SDL_Rect get_block_render_pos(const flat::Block &block) {
    return {block.x * 16 * SCALE, block.y * 16 * SCALE, 16 * SCALE, 16 * SCALE};
}

void render_block(flat::State &state, const flat::Block &block) {
    SDL_Rect src = get_block_texture(block.type);
    SDL_Rect dst = get_block_render_pos(block);
    if (SDL_RenderCopy(state.rend, state.atlas, &src, &dst) < 0)
        printf("Rendering block %d, %d failed\n", block.x, block.y);
}

void flat::render(flat::State &state) {
    SDL_SetRenderDrawColor(state.rend, 100, 203, 255, 0);
    SDL_RenderClear(state.rend);

    for (auto const &chunk : state.chunks) {
        for (auto const &block : chunk->blocks) {
            printf("Rendering block at %d, %d\n", block.x, block.y);
            render_block(state, block);
        }
    }

    SDL_Rect viewport{(state.player.x * 16) + 400,
                      (state.player.y * 16) + 300,
                      800,
                      600};

    SDL_RenderSetViewport(state.rend, &viewport);
    SDL_RenderPresent(state.rend);
}

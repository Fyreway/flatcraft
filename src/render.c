#include "render.h"

#include <SDL.h>
#include <SDL_image.h>

#include "block.h"
#include "chunk.h"
#include "util.h"

#define SCALE 4

SDL_Rect get_block_texture(BlockType type) {
    return (SDL_Rect){.x = (type % 16) * 16,
                      .y = (type / 16) * 16,
                      .w = 16,
                      .h = 16};
}

SDL_Rect get_block_render_pos(const Block *const block) {
    return (SDL_Rect){.x = block->x * 16 * SCALE,
                      .y = block->y * 16 * SCALE,
                      .w = 16 * SCALE,
                      .h = 16 * SCALE};
}

SDL_Rect get_viewport(GameState game_state) {
    return (SDL_Rect){.x = (game_state.player.x * 16) + 400,
                      .y = (game_state.player.y * 16) + 300,
                      .w = 800,
                      .h = 600};
}

void render_block(SdlState *sdl_state, const Block *const block) {
    SDL_Rect src = get_block_texture(block->type);
    SDL_Rect dst = get_block_render_pos(block);
    if (SDL_RenderCopy(sdl_state->rend, sdl_state->atlas, &src, &dst) < 0)
        printf("Rendering block %ld, %ld failed\n", block->x, block->y);
}

void render(State *state) {
    SDL_SetRenderDrawColor(state->sdl_state.rend, 100, 203, 255, 0);
    SDL_RenderClear(state->sdl_state.rend);

    for (range(state->game_state.chunks->len)) {
        Chunk *chunk = (Chunk *)state->game_state.chunks->arr[i];
        for (jrange(chunk->blocks->len)) {
            Block *block = (Block *)Vec_get_ptr(chunk->blocks, j);
            printf("Rendering block at %ld, %ld\n", block->x, block->y);
            render_block(&state->sdl_state, block);
        }
    }

    SDL_Rect viewport = get_viewport(state->game_state);
    SDL_RenderSetViewport(state->sdl_state.rend, &viewport);
    SDL_RenderPresent(state->sdl_state.rend);
}

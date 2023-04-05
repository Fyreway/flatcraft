#include "render.h"

#include <SDL.h>
#include <SDL_image.h>

#include "block.h"

#define SCALE 4

SDL_Rect get_block_texture(BlockType type) {
    return (SDL_Rect){.x = (type % 16) * 16,
                      .y = (type / 16) * 16,
                      .w = 16,
                      .h = 16};
}

SDL_Rect get_block_render_pos(Block block) {
    return (SDL_Rect){.x = block.x * 16 * SCALE,
                      .y = block.y * 16 * SCALE,
                      .w = 16 * SCALE,
                      .h = 16 * SCALE};
}

SDL_Rect get_viewport(GameState game_state) {
    return (SDL_Rect){.x = (game_state.player.x * 16) + 400,
                      .y = (game_state.player.y * 16) + 300,
                      .w = 800,
                      .h = 600};
}

void render_block(SdlState *sdl_state, Block block) {
    SDL_Rect src = get_block_texture(block.type);
    SDL_Rect dst = get_block_render_pos(block);
    SDL_RenderCopy(sdl_state->rend, sdl_state->atlas, &src, &dst);
}

void render(State *state) {
    SDL_SetRenderDrawColor(state->sdl_state.rend, 100, 203, 255, 0);
    SDL_RenderClear(state->sdl_state.rend);

    Block block = {.x = 0, .y = 0, .type = BlockType_Stone};
    render_block(&state->sdl_state, block);

    SDL_Rect viewport = get_viewport(state->game_state);
    SDL_RenderSetViewport(state->sdl_state.rend, &viewport);
    SDL_RenderPresent(state->sdl_state.rend);
}

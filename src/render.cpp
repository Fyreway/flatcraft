#include "render.hpp"

#include "block.hpp"

#define SCALE       4
#define BLOCK_SIZE  16
#define PIXEL_SCALE SCALE *BLOCK_SIZE

SDL_Rect scale(const SDL_Rect &src, int scale) {
    return {src.x * scale, src.y * scale, src.w * scale, src.h * scale};
}

SDL_Rect get_block_texture(flat::Block::Type type) {
    return scale({static_cast<int>(type) % BLOCK_SIZE,
                  static_cast<int>(type) / BLOCK_SIZE,
                  1,
                  1},
                 BLOCK_SIZE);
}

SDL_Rect get_block_render_pos(const flat::Player &player,
                              const flat::Coords &normalized_pos) {
    const auto &[block_x, block_y] = normalized_pos;
    return {static_cast<int>(std::round((block_x - player.x) * PIXEL_SCALE))
                + WIDTH / 2,
            static_cast<int>(std::round(-(block_y - player.y) * PIXEL_SCALE))
                + HEIGHT / 2,
            PIXEL_SCALE,
            PIXEL_SCALE};
}

SDL_Rect get_render_pos(const flat::Player &player, const flat::Coords &pos) {
    const auto &[block_x, block_y] = pos;
    return {static_cast<int>(std::round((block_x - player.x) * PIXEL_SCALE))
                + WIDTH / 2,
            static_cast<int>(std::round(-(block_y - player.y) * PIXEL_SCALE))
                + HEIGHT / 2,
            PIXEL_SCALE,
            PIXEL_SCALE};
}

void render_block(flat::State &state, const flat::Block &block, int chunk_pos) {
    SDL_Rect src = get_block_texture(block.type);
    SDL_Rect dst = get_block_render_pos(
        state.player,
        flat::Chunk::normalize_block_pos(chunk_pos, block.pos));
#define LEAF_COLOR 62, 209, 25
    if (block.type == flat::Block::Type::Leaves)
        SDL_SetTextureColorMod(state.atlas, LEAF_COLOR);
    else
        SDL_SetTextureColorMod(state.atlas, 255, 255, 255);
#undef LEAF_COLOR
    SDL_RenderCopy(state.rend, state.atlas, &src, &dst);
}

void render_player(flat::State &state) {
    SDL_Rect steve_src{168, 0, 16 * 8, 32 * 8};
    SDL_Rect steve_dst{(WIDTH - PIXEL_SCALE) / 2,
                       (HEIGHT - 4 * PIXEL_SCALE) / 2,
                       PIXEL_SCALE,
                       2 * PIXEL_SCALE};
    SDL_RenderCopy(state.rend, state.steve, &steve_src, &steve_dst);

    if (state.player.targeted.has_value()) {
        const auto &[mx, my] = state.player.targeted.value();
        SDL_SetRenderDrawColor(state.rend, 255, 255, 255, 100);
        SDL_SetRenderDrawBlendMode(state.rend, SDL_BLENDMODE_BLEND);

        SDL_Rect target = get_render_pos(state.player, {mx, my});

        SDL_RenderFillRect(state.rend, &target);
    }
}

void flat::render(flat::State &state) {
    SDL_SetRenderDrawColor(state.rend, 100, 203, 255, 0);
    SDL_RenderClear(state.rend);

    for (const auto &pos : state.player.near_chunks)
        for (const auto &[_, block] : state.chunks.at(pos)->blocks)
            render_block(state, block, pos);

    render_player(state);

    SDL_RenderPresent(state.rend);
}

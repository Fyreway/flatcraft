#include "SDL_surface.h"
#include "state.hpp"

#define SCALE       4
#define BLOCK_SIZE  16
#define PIXEL_SCALE SCALE *BLOCK_SIZE

SDL_Rect scale(const SDL_Rect &src, int scale) {
    return {src.x * scale, src.y * scale, src.w * scale, src.h * scale};
}

SDL_Rect get_block_texture(flat::Block::Type type) {
    return scale(
        {static_cast<int>(type) % 32, static_cast<int>(type) / 32, 1, 1},
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

void draw_block(SDL_Renderer *rend,
                SDL_Texture *atlas,
                SDL_Rect *src,
                SDL_Rect *dst,
                flat::Block::Type type) {
#define LEAF_COLOR 62, 209, 25
    if (type == flat::Block::Type::Leaves)
        SDL_SetTextureColorMod(atlas, LEAF_COLOR);
    else
        SDL_SetTextureColorMod(atlas, 255, 255, 255);
#undef LEAF_COLOR
    SDL_RenderCopy(rend, atlas, src, dst);
}

void flat::State::render_block(const flat::Block &block, int chunk_pos) {
    SDL_Rect src = get_block_texture(block.type);
    SDL_Rect dst = get_block_render_pos(
        player,
        flat::Chunk::normalize_block_pos(chunk_pos, block.pos));

    draw_block(rend, atlas, &src, &dst, block.type);
}

void flat::State::render_player() {
    SDL_Rect steve_src{168, 0, 16 * 8, 32 * 8};
    SDL_Rect steve_dst{(WIDTH - PIXEL_SCALE) / 2,
                       (HEIGHT - 4 * PIXEL_SCALE) / 2,
                       PIXEL_SCALE,
                       2 * PIXEL_SCALE};
    SDL_RenderCopy(rend, steve, &steve_src, &steve_dst);

    if (player.targeted.has_value()) {
        const auto &[mx, my] = player.targeted.value();
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 100);
        SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

        SDL_Rect target = get_render_pos(player, {mx, my});

        SDL_RenderFillRect(rend, &target);
    }
}

void flat::State::render_block_select() {
    std::pair<Block::Type, int> type =
        player.blocks.at(player.focused_mat.value());
    SDL_Rect src = get_block_texture(type.first);
    SDL_Rect dst{15, 15, PIXEL_SCALE / 2, PIXEL_SCALE / 2};
    SDL_Rect border{0, 0, PIXEL_SCALE / 2 + 30, PIXEL_SCALE / 2 + 30};

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 100);
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rend, &border);

    draw_block(rend, atlas, &src, &dst, type.first);

    SDL_Surface *surf =
        TTF_RenderUTF8_Blended(font,
                               std::to_string(type.second).c_str(),
                               SDL_Color{255, 255, 255, 255});

    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);

    int w, h;

    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

    SDL_Rect txtsrc{PIXEL_SCALE / 2 + 30 - w - 5, PIXEL_SCALE / 2, w, h};

    SDL_RenderCopy(rend, tex, nullptr, &txtsrc);

    SDL_DestroyTexture(tex);
}

void flat::State::render() {
    SDL_SetRenderDrawColor(rend, 100, 203, 255, 0);
    SDL_RenderClear(rend);

    for (const auto &pos : player.near_chunks)
        for (const auto &[_, block] : chunks.at(pos)->blocks)
            render_block(block, pos);

    render_player();

    if (player.focused_mat.has_value()) render_block_select();

    SDL_RenderPresent(rend);
}

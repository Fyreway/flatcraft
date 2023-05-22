#include "state.hpp"

#include <SDL_image.h>
#include <numeric>
#include <random>
#include "block.hpp"

flat::State::State() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) util::error_sdl("SDL init");
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        util::error_sdl("SDL_image init");

    win = SDL_CreateWindow("flatcraft",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           WIDTH,
                           HEIGHT,
                           0);
    if (win == nullptr) util::error_sdl("window creation");

    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (rend == nullptr) util::error_sdl("renderer acquisition");

    // TODO: normalize path
    atlas = IMG_LoadTexture(rend, "../res/terrain.png");
    steve = IMG_LoadTexture(rend, "../res/steve.png");

    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(),
                 perm.end(),
                 std::default_random_engine(time(nullptr)));

    for (int i = -4; i < 4; i++)
        chunks.insert(
            {i, std::make_unique<Chunk>(Chunk::build_simplex(i, perm))});

    player = Player(0.5, 60, chunks);
}

flat::State::~State() {
    SDL_DestroyTexture(atlas);
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);

    SDL_Quit();
    IMG_Quit();
}

void flat::State::update() {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    player.update(chunks, mx, my);
}

void flat::State::change_block(const Coords &pos,
                               const std::optional<Block::Type> &type) {
    const auto &[x, y] = pos;

    if (x == floor(player.x)
        && (y == ceil(player.y) + 1 || y == ceil(player.y) + 2))
        return;

    int chunk_pos = floor(x / 8.0);

    if (type.has_value()) {
        if (chunks.find(chunk_pos) == chunks.end())
            chunks.insert(
                {chunk_pos,
                 std::make_unique<Chunk>(Chunk::build_empty(chunk_pos))});

        auto &chunk = chunks.at(chunk_pos);

        chunk->blocks.emplace(
            chunk->abnormalize_block_pos({x, y}),
            Block(chunk->abnormalize_block_pos({x, y}), type.value()));
    } else {
        if (chunks.find(chunk_pos) != chunks.end()) {
            auto &chunk = chunks.at(chunk_pos);
            const auto ab_pos = chunk->abnormalize_block_pos({x, y});
            const auto &it = chunk->blocks.find(ab_pos);
            if (it != chunk->blocks.end()
                && it->second.type != Block::Type::Bedrock)
                chunk->blocks.erase(ab_pos);
            if (chunk->blocks.empty()) chunks.erase(chunk_pos);
        }
    }
}

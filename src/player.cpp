#include "player.hpp"

#include <cmath>
#include <iostream>

#include "block.hpp"
#include "chunk.hpp"

std::vector<int> get_near_chunks(const flat::Chunks &chunks,
                                 const flat::Player &player) {
    std::vector<int> indices;
    for (auto const &[pos, _] : chunks)
        if (std::abs(pos - player.chunk_x) < 3) indices.push_back(pos);
    return indices;
}

flat::Player::Player(double x, double y, const Chunks &chunks) : x(x), y(y) {
    chunk_x = util::f_trunc(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

void flat::Player::update(const Chunks &chunks, int mx, int my) {
    update_pos(chunks);
    update_target(mx, my);
}

void flat::Player::update_pos(const Chunks &chunks) {
    // std::cout << "Player pos: " << x << ' ' << y << std::endl;

    chunk_x = util::f_floor(x / 8);

    if (chunks.find(chunk_x) == chunks.end()) {
        stopped = false;
        y += gravity;
        return;
    }

    const auto &chunk = chunks.at(chunk_x);

    if (chunk->blocks.find(chunk->abnormalize_block_pos(
            {util::f_floor(x), util::f_ceil(y + 2)}))
        != chunk->blocks.end()) {
        vert_vel = 0;
    } else {
        y += vert_vel;
        vert_vel *= 0.8;
    }
    if (chunk->blocks.find(
            chunk->abnormalize_block_pos({util::f_floor(x), util::f_ceil(y)}))
        != chunk->blocks.end()) {
        stopped = true;
        y = util::f_ceil(y);
        vert_vel = 0;
    } else {
        y += gravity;
        stopped = false;
    }

    if (y == -64)
        ;  // TODO

    chunk_x = util::f_floor(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

void flat::Player::update_target(int mx, int my) {
    targeted = {std::ceil((mx - 400 - 32) / 64.0) + util::f_floor(x),
                std::ceil(-(my - 300) / 64.0) + util::f_ceil(y)};
    if (util::distance(targeted.value(), std::pair{x - 0.5, y + 1}) > 4)
        targeted.reset();
    // std::cout << "Targeted: " << targeted->first << ' ' << targeted->second
    //           << std::endl;
}

void flat::Player::move(const Chunks &chunks, double amount) {
    double pot_x = x + amount;

    int pot_chunk_x = util::f_floor(pot_x / 8);

    if (chunks.find(pot_chunk_x) == chunks.end()) {
        x = pot_x;
        return;
    }

    const auto &chunk = chunks.at(pot_chunk_x);

    if (chunk->blocks.find(chunk->abnormalize_block_pos(
            {util::f_floor(pot_x), util::f_ceil(y + 1)}))
            == chunk->blocks.end()
        && chunk->blocks.find(chunk->abnormalize_block_pos(
               {util::f_floor(pot_x), util::f_ceil(y + 2)}))
               == chunk->blocks.end())
        x = pot_x;
    chunk_x = util::f_floor(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

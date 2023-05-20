#include "player.hpp"

#include <cmath>
#include <iostream>

#include "block.hpp"
#include "chunk.hpp"

std::vector<int> get_near_chunks(const flat::Chunks &chunks,
                                 const flat::Player &player) {
    std::vector<int> indices;
    for (auto const &[pos, chunk] : chunks) {
        if (std::abs(pos - player.chunk_x) < 3) indices.push_back(pos);
    }
    return indices;
}

flat::Player::Player(double x, double y, const Chunks &chunks) : x(x), y(y) {
    chunk_x = std::trunc(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

void flat::Player::update(const Chunks &chunks) {
    std::cout << "Player pos: " << x << ' ' << y << std::endl;

    chunk_x = std::trunc(x / 8);

    if (chunks.find(chunk_x) == chunks.end()) {
        stopped = false;
        y += gravity;
        return;
    }

    const auto &chunk = chunks.at(chunk_x);

    if (chunk->blocks.find(
            chunk->abnormalize_block_pos({std::trunc(x), std::ceil(y)}))
        != chunk->blocks.end()) {
        stopped = true;
    } else {
        y += gravity;
        stopped = false;
    }

    chunk_x = std::trunc(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

void flat::Player::move(const Chunks &chunks, double amount) {
    double pot_x = x + amount;

    int pot_chunk_x = std::trunc(pot_x / 8);

    if (chunks.find(pot_chunk_x) == chunks.end()) {
        x = pot_x;
        return;
    }

    const auto &chunk = chunks.at(pot_chunk_x);

    if (chunk->blocks.find(
            chunk->abnormalize_block_pos({std::trunc(pot_x), std::ceil(y + 1)}))
        == chunk->blocks.end()) {
        x = pot_x;
    }
    chunk_x = std::trunc(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

#include "player.hpp"

#include <cmath>

#include "util.hpp"

std::vector<std::size_t> get_near_chunks(
    const std::vector<std::unique_ptr<flat::Chunk>> &chunks,
    const flat::Player &player) {
    std::vector<std::size_t> indices;
    for (range(chunks.size())) {
        auto const &chunk = chunks.at(i);
        if (std::abs(chunk->x - player.chunk_x) < 3
            && std::abs(chunk->y - player.chunk_y) < 3)
            indices.push_back(i);
    }
    return indices;
}

flat::Player::Player(double x,
                     double y,
                     const std::vector<std::unique_ptr<Chunk>> &chunks)
    : x(x),
      y(-y) {
    update(chunks);
}

void flat::Player::update(const std::vector<std::unique_ptr<Chunk>> &chunks) {
    vert_vel += gravity;
    y += vert_vel;

    chunk_x = std::floor(x / 8);
    chunk_y = std::floor(y / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

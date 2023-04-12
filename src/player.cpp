#include "player.hpp"

#include <cmath>

std::vector<std::pair<int, int>> get_near_chunks(
    const std::unordered_map<std::pair<int, int>,
                             std::unique_ptr<flat::Chunk>,
                             util::pair_hash> &chunks,
    const flat::Player &player) {
    std::vector<std::pair<int, int>> indices;
    for (auto const &[coords, chunk] : chunks) {
        auto const &[x, y] = coords;
        if (std::abs(x - player.chunk_x) < 3
            && std::abs(y - player.chunk_y) < 3)
            indices.push_back(coords);
    }
    return indices;
}

flat::Player::Player(double x,
                     double y,
                     const std::unordered_map<std::pair<int, int>,
                                              std::unique_ptr<flat::Chunk>,
                                              util::pair_hash> &chunks)
    : x(x),
      y(-y) {
    update(chunks);
}

void flat::Player::update(const std::unordered_map<std::pair<int, int>,
                                                   std::unique_ptr<Chunk>,
                                                   util::pair_hash> &chunks) {
    vert_vel += gravity;
    y += vert_vel;

    chunk_x = std::floor(x / 8);
    chunk_y = std::floor(y / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

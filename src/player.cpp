#include "player.hpp"
#include <optional>

std::vector<int> get_near_chunks(const flat::Chunks &chunks,
                                 const flat::Player &player) {
    std::vector<int> indices;
    for (auto const &[pos, _] : chunks)
        if (abs(pos - player.chunk_x) < 3) indices.push_back(pos);
    return indices;
}

flat::Player::Player(double x, double y, const Chunks &chunks) : x(x), y(y) {
    chunk_x = trunc(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

void flat::Player::update(const Chunks &chunks, int mx, int my) {
    update_pos(chunks);
    update_target(mx, my);

    if (focused_mat.has_value() && focused_mat.value() >= inventory.size())
        focused_mat = std::nullopt;
}

void flat::Player::update_pos(const Chunks &chunks) {
    // std::cout << "Player pos: " << x << ' ' << y << std::endl;

    chunk_x = floor(x / 8);

    if (chunks.find(chunk_x) == chunks.end()) {
        stopped = false;
        y += gravity;
        return;
    }

    const auto &chunk = chunks.at(chunk_x);

    if (chunk->blocks.find(
            chunk->abnormalize_block_pos({floor(x), ceil(y + 2)}))
        != chunk->blocks.end()) {
        vert_vel = 0;
    } else {
        y += vert_vel;
        vert_vel *= 0.8;
    }
    if (chunk->blocks.find(chunk->abnormalize_block_pos({floor(x), ceil(y)}))
        != chunk->blocks.end()) {
        stopped = true;
        y = ceil(y);
        vert_vel = 0;
    } else {
        y += gravity;
        stopped = false;
    }

    if (ceil(y) < -64) {
        y = 64;
        stopped = true;
        vert_vel = 0;
    }

    chunk_x = floor(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

void flat::Player::update_target(int mx, int my) {
    targeted = {ceil((mx - 400 - 32) / 64.0) + floor(x),
                ceil(-(my - 300) / 64.0) + ceil(y)};
    if (util::distance(targeted.value(), std::pair{x - 0.5, y + 1}) > 4)
        targeted.reset();
    // std::cout << "Targeted: " << targeted->first << ' ' << targeted->second
    //           << std::endl;
}

void flat::Player::move(const Chunks &chunks, double amount) {
    double pot_x = x + amount;

    int pot_chunk_x = floor(pot_x / 8);

    if (chunks.find(pot_chunk_x) == chunks.end()) {
        x = pot_x;
        return;
    }

    const auto &chunk = chunks.at(pot_chunk_x);

    if (chunk->blocks.find(
            chunk->abnormalize_block_pos({floor(pot_x), ceil(y + 1)}))
            == chunk->blocks.end()
        && chunk->blocks.find(
               chunk->abnormalize_block_pos({floor(pot_x), ceil(y + 2)}))
               == chunk->blocks.end())
        x = pot_x;
    chunk_x = floor(x / 8);
    near_chunks = get_near_chunks(chunks, *this);
}

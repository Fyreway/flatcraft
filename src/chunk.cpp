#include "chunk.hpp"

#include <SimplexNoise.h>

flat::Chunk::Chunk(int pos, const Blocks &blocks) : pos(pos), blocks(blocks) {}

flat::Chunk flat::Chunk::build_flat(int pos) {
    Blocks blocks;

    for (int i = 0; i < 8; i++) {
        blocks.insert({{i, 0}, {{i, 0}, Block::Type::Grass}});
        blocks.insert({{i, -1}, {{i, -1}, Block::Type::Dirt}});
        blocks.insert({{i, -2}, {{i, -2}, Block::Type::Dirt}});
        for (int j = -2; j >= -63; j--)
            blocks.insert({{i, j}, {{i, j}, Block::Type::Stone}});
        blocks.insert({{i, -64}, {{i, -64}, Block::Type::Bedrock}});
    }

    return Chunk(pos, blocks);
}

flat::Chunk flat::Chunk::build_empty(int pos) { return Chunk(pos, {}); }

flat::Block &flat::Chunk::get_block(const Coords &pos) {
    return blocks.at(pos);
}

flat::Coords flat::Chunk::normalize_block_pos(const Coords &block_pos) const {
    return Chunk::normalize_block_pos(pos, block_pos);
}

flat::Coords flat::Chunk::abnormalize_block_pos(const Coords &block_pos) const {
    return Chunk::abnormalize_block_pos(pos, block_pos);
}

flat::Coords flat::Chunk::normalize_block_pos(int chunk_pos,
                                              const Coords &block_pos) {
    const auto &[block_x, block_y] = block_pos;
    return {block_x + chunk_pos * 8, block_y};
}

flat::Coords flat::Chunk::abnormalize_block_pos(int chunk_pos,
                                                const Coords &block_pos) {
    const auto &[block_x, block_y] = block_pos;
    return {block_x - chunk_pos * 8, block_y};
}

flat::Chunk flat::Chunk::build_terrain(
    int pos,
    const std::array<uint8_t, 256> &perm,
    std::mt19937 &gen,
    std::uniform_int_distribution<int> &dist) {
    Blocks blocks;

    int tree_pos = dist(gen);

    for (int i = 0; i < 8; i++) {
        float val =
            SimplexNoise::noise(static_cast<float>(pos * 8 + i) / 100, perm);
        val +=
            SimplexNoise::noise(static_cast<float>(pos * 8 + i) / 60.5, perm);
        int y = ceil(val * 10);
        blocks.insert({{i, y}, {{i, y}, Block::Type::Grass}});

        if (i == tree_pos && dist(gen) == 5) {
            int j = y + 1;
            for (; j < y + dist(gen); j++)
                blocks.insert({{i, j}, {{i, j}, Block::Type::Log}});
            for (int i2 = i - 2; i2 <= i + 2; i2++)
                blocks.insert({{i2, j}, {{i2, j}, Block::Type::Leaves}});
            for (int i2 = i - ((dist(gen) == 3) ? 1 : 2);
                 i2 <= i + ((dist(gen) == 3) ? 1 : 2);
                 i2++)
                blocks.insert(
                    {{i2, j + 1}, {{i2, j + 1}, Block::Type::Leaves}});
            for (int i2 = i - 1; i2 <= i + 1; i2++) {
                blocks.insert(
                    {{i2, j + 2}, {{i2, j + 2}, Block::Type::Leaves}});
                blocks.insert(
                    {{i2, j + 3}, {{i2, j + 3}, Block::Type::Leaves}});
            }
        }
        int j = y;
        for (; j >= y - rand() % 4 - 1; j--)
            blocks.insert({{i, j}, {{i, j}, Block::Type::Dirt}});

        for (; j >= -63; j--)
            blocks.insert({{i, j}, {{i, j}, Block::Type::Stone}});

        blocks.insert({{i, -64}, {{i, -64}, Block::Type::Bedrock}});
    }

    return Chunk(pos, blocks);
}

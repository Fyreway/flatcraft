#include "chunk.hpp"

#include "util.hpp"

flat::Chunk::Chunk(int pos, const Blocks &blocks) : pos(pos), blocks(blocks) {}

flat::Chunk flat::Chunk::build_flat(int pos) {
    Blocks blocks;

    for (range(8)) blocks.insert({{i, 0}, {{i, 0}, Block::Type::Stone}});
    blocks.erase({5, 0});
    blocks.insert({{5, -1}, {{5, -1}, Block::Type::Stone}});

    // blocks.insert({{2, 2}, {{2, 2}, Block::Type::Bedrock}});
    blocks.insert({{2, 1}, {{2, 1}, Block::Type::Stone}});

    return Chunk(pos, blocks);
}

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

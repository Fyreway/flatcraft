#include "chunk.hpp"

#include "util.hpp"

flat::Chunk::Chunk(const std::vector<Block> &blocks) : blocks(blocks) {}

flat::Chunk flat::Chunk::build_flat() {
    std::vector<Block> blocks;

    for (range(8)) {
        blocks.emplace_back(i, 0, Block::Type::Stone);
        blocks.emplace_back(i, 1, Block::Type::Leaves);
    }

    return Chunk(blocks);
}

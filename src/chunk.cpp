#include "chunk.hpp"

#include "util.hpp"

flat::Chunk::Chunk(int x, int y, const std::vector<Block> &blocks)
    : x(x),
      y(y),
      blocks(blocks) {}

flat::Chunk flat::Chunk::build_flat(int x, int y) {
    std::vector<Block> blocks;

    for (range(8)) blocks.emplace_back(8 * x + i, 0, Block::Type::Stone);

    return Chunk(x, y, blocks);
}

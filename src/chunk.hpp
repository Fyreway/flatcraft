#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <random>
#include <unordered_map>
#include <vector>

#include "block.hpp"
#include "util.hpp"

namespace flat {
    using Blocks = std::unordered_map<Coords, Block, util::pair_hash>;

    class Chunk {
    public:
        const int pos;
        Blocks blocks;

        static Chunk build_flat(int pos);
        static Chunk build_empty(int pos);
        static Chunk build_terrain(int pos,
                                   const std::array<uint8_t, 256> &perm,
                                   std::mt19937 &gen,
                                   std::uniform_int_distribution<int> &dist);

        Block &get_block(const Coords &pos);

        Coords normalize_block_pos(const Coords &block_pos) const;
        Coords abnormalize_block_pos(const Coords &block_pos) const;
        static Coords normalize_block_pos(int chunk_pos,
                                          const Coords &block_pos);

        static Coords abnormalize_block_pos(int chunk_pos,
                                            const Coords &block_pos);

    private:
        Chunk(int pos, const Blocks &blocks);
    };

    using Chunks = std::unordered_map<int, std::unique_ptr<Chunk>>;

}  // namespace flat

#endif

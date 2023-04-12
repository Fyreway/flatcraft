#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <vector>

#include "block.hpp"

namespace flat {
    class Chunk {
    public:
        std::vector<Block> blocks;

        static Chunk build_flat();

    private:
        Chunk(const std::vector<Block> &blocks);
    };
}  // namespace flat

#endif

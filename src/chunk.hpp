#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <vector>

#include "block.hpp"

namespace flat {
    class Chunk {
    public:
        int x, y;
        std::vector<Block> blocks;

        static Chunk build_flat(int x, int y);

    private:
        Chunk(int x, int y, const std::vector<Block> &blocks);
    };
}  // namespace flat

#endif

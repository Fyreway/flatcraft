#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include <vector>

#include "chunk.hpp"

namespace flat {
    class Player {
    public:
        double x, y;
        int chunk_x, chunk_y;
        std::vector<std::size_t> near_chunks;

        Player() = default;
        Player(double x,
               double y,
               const std::vector<std::unique_ptr<Chunk>> &chunks);

        void update(const std::vector<std::unique_ptr<Chunk>> &chunks);
    };
}  // namespace flat

#endif

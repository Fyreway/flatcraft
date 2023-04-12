#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include <vector>

#include "chunk.hpp"
#include "util.hpp"

namespace flat {
    class Player {
    public:
        double x, y;
        int chunk_x, chunk_y;
        std::vector<std::pair<int, int>> near_chunks;
        double vert_vel = 0;
        double gravity = 0.5;

        Player() = default;
        Player(double x,
               double y,
               const std::unordered_map<std::pair<int, int>,
                                        std::unique_ptr<Chunk>,
                                        util::pair_hash> &chunks);

        void update(const std::unordered_map<std::pair<int, int>,
                                             std::unique_ptr<Chunk>,
                                             util::pair_hash> &chunks);
    };
}  // namespace flat

#endif

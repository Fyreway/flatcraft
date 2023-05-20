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
        int chunk_x;
        std::vector<int> near_chunks;
        // double vert_vel = 0;
        bool stopped = false;
        double gravity = -0.5;

        Player() = default;
        Player(double x, double y, const Chunks &chunks);

        void update(const Chunks &chunks);

        void move(const Chunks &chunks, double amount);
    };
}  // namespace flat

#endif

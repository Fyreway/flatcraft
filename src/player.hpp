#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include <optional>

#include "chunk.hpp"

namespace flat {
    class Player {
    public:
        double x, y;
        int chunk_x;
        std::vector<int> near_chunks;
        double vert_vel = 0;
        bool stopped = false;
        double gravity = -0.5;

        std::optional<Coords> targeted;

        std::vector<std::pair<Block::Type, int>> blocks;

        std::optional<int> focused_mat;

        Player() = default;
        Player(double x, double y, const Chunks &chunks);

        void update(const Chunks &chunks, int mx, int my);

        void move(const Chunks &chunks, double amount);

    private:
        void update_pos(const Chunks &chunks);
        void update_target(int mx, int my);
    };
}  // namespace flat

#endif

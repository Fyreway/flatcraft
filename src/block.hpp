#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <utility>

namespace flat {
    using Coords = std::pair<int, int>;

    class Block {
    public:
        Coords pos;
        enum class Type {
            Stone = 32 * 9 + 20,
            Dirt = 32 * 6 + 8,
            Grass = 32 * 10 + 12,
            Planks = 32 * 4 + 16,
            Bricks = 32 * 3 + 5,
            Cobblestone = 32 * 5 + 3,
            Bedrock = 32 * 3 + 4,
            Log = 32 * 14 + 3,
            Leaves = 32 * 13 + 4,
        } type;

        Block(const Coords &pos, Type type);
    };
}  // namespace flat

#endif

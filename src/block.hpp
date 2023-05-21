#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <utility>

namespace flat {
    using Coords = std::pair<int, int>;

    class Block {
    public:
        Coords pos;
        enum class Type {
            Stone = 1,
            Dirt,
            Grass,
            Planks,
            Cobblestone = 16,
            Bedrock,
            Log = 20,
            Leaves = 53,
        } type;

        Block(const Coords &pos, Type type);
    };
}  // namespace flat

#endif

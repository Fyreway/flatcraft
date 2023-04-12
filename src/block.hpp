#ifndef __BLOCK_H__
#define __BLOCK_H__

namespace flat {
    class Block {
    public:
        const int x, y;
        enum class Type { Grass, Stone, Dirt } type;

        Block(int x, int y, Type type);
    };
}  // namespace flat

#endif

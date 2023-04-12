#ifndef __BLOCK_H__
#define __BLOCK_H__

namespace flat {
    class Block {
    public:
        const int x, y;
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

        Block(int x, int y, Type type);
    };
}  // namespace flat

#endif

#ifndef __BLOCK_H__
#define __BLOCK_H__

typedef enum { BlockType_Grass, BlockType_Stone, BlockType_Dirt } BlockType;

typedef struct {
    long x, y;
    BlockType type;
} Block;

Block *Block_new(long x, long y, BlockType type);

void Block_destroy(Block *block);

#endif

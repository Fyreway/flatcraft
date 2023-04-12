#include "block.h"

#include <stdlib.h>

Block *Block_new(long x, long y, BlockType type) {
    Block *block = malloc(sizeof(Block));
    block->x = x;
    block->y = y;
    block->type = type;
    return block;
}

void Block_destroy(Block *block) { free(block); }

#include "chunk.h"

#include <stdlib.h>

#include "block.h"
#include "util.h"

Chunk *Chunk_new() { return malloc(sizeof(Chunk)); }

Chunk *build_flat(int x, int y) {
    Vec *blocks = Vec_new();

    for (range(8)) {
        Vec_push_ptr(blocks, (void *)Block_new(8 * x + i, 0, BlockType_Stone));
    }

    Chunk *chunk = Chunk_new();
    chunk->blocks = blocks;
    chunk->x = x;
    chunk->y = y;
    return chunk;
}

void Chunk_destroy(Chunk *chunk) {
    Vec_destroy(chunk->blocks);
    free(chunk);
}

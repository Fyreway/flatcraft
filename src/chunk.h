#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <vec/vec.h>

typedef struct {
    int x, y;
    Vec *blocks;
} Chunk;

Chunk *build_flat(int x, int y);

void Chunk_destroy(Chunk *chunk);

#endif

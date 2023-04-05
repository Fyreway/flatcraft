#include "vec/vec.h"

#include <stdlib.h>

Vec *Vec_new() {
    Vec *vec = malloc(sizeof(Vec));
    vec->len = 0;
    vec->cap = VEC_INIT_CAPACITY;
    vec->arr = malloc(sizeof(ptr) * vec->cap);
    return vec;
}

void Vec_destroy(Vec *vec) {
    foreach (e, vec) free(e);
    free(vec);
}

void I_Vec_push(Vec *const vec, ptr val) {
    if (vec->len == vec->cap) {
        vec->cap *= 2;
        vec->arr = realloc(vec->arr, vec->cap);
    }
    vec->arr[vec->len++] = val;
}

ptr I_Vec_pop(Vec *const vec) {
    ptr e = vec->arr[vec->len - 1];
    vec->arr[--vec->len] = NULL;
    return e;
}

ptr I_Vec_get(const Vec *const vec, unsigned long idx) {
    return idx >= vec->len ? NULL : vec->arr[idx];
}

void I_Vec_set(Vec *const vec, unsigned long idx, ptr val) {
    if (idx >= vec->len) return;
    vec->arr[idx] = val;
}

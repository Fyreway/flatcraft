#include "vec/vec.h"

#include <stdlib.h>

Vec *Vec_new() {
    Vec *vec = malloc(sizeof(Vec));
    vec->len = 0;
    vec->cap = VEC_INIT_CAPACITY;
    vec->arr = calloc(vec->cap, sizeof(void *));
    return vec;
}

void Vec_destroy(Vec *vec) {
    for (unsigned long i = 0; i < vec->len; i++) free(vec->arr[i]);
    free(vec->arr);
    free(vec);
}

void Vec_push_ptr(Vec *const vec, void *val) {
    if (vec->len == vec->cap) {
        vec->cap *= 2;
        vec->arr = realloc(vec->arr, vec->cap * sizeof(void *));
    }
    vec->arr[vec->len++] = val;
}

void *Vec_pop_ptr(Vec *const vec) {
    void *e = vec->arr[vec->len - 1];
    vec->arr[--vec->len] = NULL;
    return e;
}

void *Vec_get_ptr(const Vec *const vec, unsigned long idx) {
    return idx >= vec->len ? NULL : vec->arr[idx];
}

void Vec_set_ptr(Vec *const vec, unsigned long idx, void *val) {
    if (idx >= vec->len) return;
    vec->arr[idx] = val;
}

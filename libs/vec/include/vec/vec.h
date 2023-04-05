#ifndef __VEC_H__
#define __VEC_H__

#define VEC_INIT_CAPACITY 4

#define ptr void *

#define foreach(name, array)    \
    unsigned long i = 0;        \
    ptr name = (array)->arr[i]; \
    while ((name = (array)->arr[++i]) && i < (array)->len)

typedef struct {
    ptr *arr;
    unsigned long len;
} Array;

typedef struct {
    ptr *arr;
    unsigned long len, cap;
} Vec;

Vec *Vec_new();

void I_Vec_push(Vec *const vec, ptr val);

#define Vec_push(vec, type, val) \
    {                            \
        type temp = val;         \
        I_Vec_push(vec, &temp);  \
    }

ptr I_Vec_pop(Vec *const vec);

#define Vec_pop(vec, type) *(type *)I_Vec_pop(vec)

ptr I_Vec_get(const Vec *const vec, unsigned long idx);

#define Vec_get(vec, idx, type) *(type *)I_Vec_get(vec, idx)

void I_Vec_set(Vec *const vec, unsigned long idx, ptr val);

#define Vec_set(vec, idx, type, val) \
    {                                \
        type temp = val;             \
        I_Vec_set(vec, idx, &temp);  \
    }

void Vec_destroy(Vec *vec);

#endif

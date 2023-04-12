#ifndef __VEC_H__
#define __VEC_H__

#define VEC_INIT_CAPACITY 4

typedef struct {
    void **arr;
    unsigned long len;
} Array;

typedef struct {
    void **arr;
    unsigned long len, cap;
} Vec;

Vec *Vec_new();

void Vec_push_ptr(Vec *const vec, void *val);

#define Vec_push(vec, type, val)  \
    {                             \
        type temp = val;          \
        Vec_push_ptr(vec, &temp); \
    }

void *Vec_pop_ptr(Vec *const vec);

#define Vec_pop(vec, type) *(type *)Vec_pop_ptr(vec)

void *Vec_get_ptr(const Vec *const vec, unsigned long idx);

#define Vec_get(vec, idx, type) *(type *)Vec_get_ptr(vec, idx)

void Vec_set_ptr(Vec *const vec, unsigned long idx, void *val);

#define Vec_set(vec, idx, type, val)  \
    {                                 \
        type temp = val;              \
        Vec_set_ptr(vec, idx, &temp); \
    }

void Vec_destroy(Vec *vec);

#endif

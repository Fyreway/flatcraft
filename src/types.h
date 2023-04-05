#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdbool.h>

typedef struct S_Option Option;

#define _Option(type) \
    struct S_Option { \
        type val;     \
        bool is_null; \
    }

#define Some(val) \
    (struct S_Option) { .val = val, .is_null = false }

#define None \
    (struct S_Option) { .is_null = true }

#define _Result(type, errtype) \
    struct Result {            \
        type val;              \
        errtype err;           \
    }

#endif

#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>

#define range_enum(name, start, end, step) \
    unsigned long name = (start);          \
    name < (end);                          \
    name += (step)

#define range_step(start, end, step) range_enum(i, start, end, step)

#define range_start(start, end) range_step(start, end, 1)

#define range(end) range_start(0, end)

namespace util {
    void error_sdl(const std::string &proc);
}

#endif

#ifndef __UTIL_H__
#define __UTIL_H__

#include <cmath>
#include <string>
#include <utility>

#define range_enum(name, start, end, step) \
    int name = (start);                    \
    name < (end);                          \
    name += (step)

#define range_step(start, end, step) range_enum(i, start, end, step)

#define range_start(start, end) range_step(start, end, 1)

#define range(end) range_start(0, end)

namespace util {
    void error_sdl(const std::string &proc);

    struct pair_hash {
        template<class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    static inline int32_t f_floor(double v) {
        int32_t i = static_cast<int32_t>(v);
        return v < i ? i - 1 : i;
    }

    static inline int32_t f_trunc(double v) { return static_cast<int32_t>(v); }

    static inline int32_t f_ceil(double v) {
        int32_t i = static_cast<int32_t>(v);
        return i < v ? i + 1 : i;
    }

    template<typename T1, typename T2>
    static inline double distance(const std::pair<T1, T1> &pos1,
                                  const std::pair<T2, T2> &pos2) {
        const auto &[x1, y1] = pos1;
        const auto &[x2, y2] = pos2;

        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }
}  // namespace util

#endif

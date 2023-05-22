#ifndef __UTIL_H__
#define __UTIL_H__

#include <cmath>
#include <string>
#include <utility>

namespace util {
    void error_sdl(const std::string &proc);

    struct pair_hash {
        template<class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    template<typename T1, typename T2>
    static inline double distance(const std::pair<T1, T1> &pos1,
                                  const std::pair<T2, T2> &pos2) {
        const auto &[x1, y1] = pos1;
        const auto &[x2, y2] = pos2;

        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
}  // namespace util

#endif

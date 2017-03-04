#ifndef HASHER_H_INCLUDED
#define HASHER_H_INCLUDED

#include <algorithm>
#include <functional>

namespace Hasher
{
    template<typename T>
    size_t hash(T x, T y, T z)
    {
        std::hash<T> hasher;
        auto h1 = hasher(x);
        auto h2 = hasher(y);
        auto h3 = hasher(z);

        return std::hash<T>{}(h1 ^ (h2 << h3) ^ h3);
    }

    template<typename T>
    size_t hash(T x, T z)
    {
        std::hash<T> hasher;
        auto h1 = hasher(x);
        auto h2 = hasher(z);

        return std::hash<T>{}((h1 ^ h2) >> 2);
    }
}

#endif // HASHER_H_INCLUDED

#ifndef HASHER_H_INCLUDED
#define HASHER_H_INCLUDED

#include <algorithm>
#include <functional>

namespace Hasher
{
    template<typename T>
    size_t hash(T x, T y, T z)
    {
        auto h1 = std::hash<T>{}(x);
        auto h2 = std::hash<T>{}(y);
        auto h3 = std::hash<T>{}(z);

        return std::hash<T>{}(h1 ^ (h2 << h3) ^ h3);
    }
}

#endif // HASHER_H_INCLUDED

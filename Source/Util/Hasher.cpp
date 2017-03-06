#include "Hasher.h"

#include <algorithm>
#include <functional>

namespace Hasher
{

    size_t hash(int integer)
    {
        integer = ~integer + (integer << 15);
        integer = integer ^ (integer >> 12);
        integer = integer + (integer << 2);
        integer = integer ^ (integer >> 4);
        integer = integer * 2057;
        return std::hash<int>{}(integer);
    }

    size_t hash(int x, int y)
    {
        size_t h1 = hash(x);
        size_t h2 = hash(y);
        return hash(h1 ^ (h2 << 2));
    }

    size_t hash (int x, int y, int z)
    {
        size_t h1 = hash(x);
        size_t h2 = hash(z);
        size_t h3 = hash(y);
        return hash(h1 ^ (h2 << 2) ^ h3);
    }
}

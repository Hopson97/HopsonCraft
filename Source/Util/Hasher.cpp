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
        size_t h1 = hash(x >> y);
        size_t h2 = hash(x << y);
        return (h1 ^ (h2 << 1));
    }

    size_t hash (int x, int y, int z)
    {
        size_t h1 = hash(x >> z);
        size_t h2 = hash(x << z);
        size_t h3 = hash(y << h1);
        return (h1 ^ (h2 << 1) ^ h3);
    }
}

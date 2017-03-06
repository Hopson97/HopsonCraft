#ifndef HASHER_H
#define HASHER_H

#include <cstdlib>

namespace Hasher
{
    size_t hash (int integer);
    size_t hash (int x, int y);
    size_t hash (int x, int y, int z);
}

#endif // HASHER_H

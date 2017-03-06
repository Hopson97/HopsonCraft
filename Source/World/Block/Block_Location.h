#ifndef BLOCK_POSITION_H
#define BLOCK_POSITION_H


#include <functional>
#include <cmath>
#include <cstdint>

#include "../../Util/Hasher.h"

struct Block_Location
{
    Block_Location (int32_t x, int32_t y, int32_t z);

    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;

    bool operator== (const Block_Location& other) const;

    bool operator!=  (const Block_Location& other) const;

    static Block_Location getRandom(int32_t maxY);
};

namespace std
{
    template<>
    struct hash<Block_Location>
    {
        size_t operator() (Block_Location const& v) const
        {
            return Hasher::hash(v.x, v.y, v.z);
        }
    };
}

#endif // BLOCK_POSITION_H

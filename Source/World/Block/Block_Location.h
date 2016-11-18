#ifndef BLOCK_POSITION_H
#define BLOCK_POSITION_H


#include <functional>
#include <cmath>

#include "../../Util/Hasher.h"

struct Block_Location
{
    Block_Location (int x, int y, int z);

    int x = 0;
    int y = 0;
    int z = 0;

    bool operator== (const Block_Location& other) const;

    bool operator!=  (const Block_Location& other) const;
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

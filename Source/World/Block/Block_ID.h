#ifndef BLOCK_ID_H_INCLUDED
#define BLOCK_ID_H_INCLUDED

#include <cstdint>

typedef uint8_t Block_t;

namespace Block
{
    enum class ID : Block_t
    {
        Air         = 0,
        Grass       = 1,
        Dirt        = 2,
        Stone       = 3,
        Sand        = 4,
        Oak_Wood    = 5,
        Oak_Leaf    = 6,
        Water       = 7,
        Rose        = 8,
        Tall_Grass  = 9,

        NUM_BLOCK_TYPES
    };
}

#endif // BLOCK_ID_H_INCLUDED

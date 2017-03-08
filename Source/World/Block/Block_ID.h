#ifndef BLOCK_ID_H_INCLUDED
#define BLOCK_ID_H_INCLUDED

#include <cstdint>

typedef uint8_t Block_t;

namespace Block
{
    enum class ID : Block_t
    {
        Air     = 0,
        Grass   = 1,
        Dirt    = 2,
        Stone   = 3,

        NUM_BLOCK_TYPES
    };
}

#endif // BLOCK_ID_H_INCLUDED

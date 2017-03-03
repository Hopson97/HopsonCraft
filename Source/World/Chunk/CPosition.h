#ifndef CPOSITION_H_INCLUDED
#define CPOSITION_H_INCLUDED

#include <functional>
#include <cstdint>

#include "../../Util/Hasher.h"

namespace Chunk
{
    struct Position
    {
        Position() = default;
        Position(uint64_t x, uint64_t y, uint64_t z);

        uint64_t    x,
                    y,
                    z;
    };
}

namespace std
{
    template<>
    class hash<Chunk::Position>
    {
        size_t operator() (const Chunk::Position& pos) const
        {
            return Hasher::hash(pos.x, pos.y, pos.z);
        }
    };
}

#endif // CPOSITION_H_INCLUDED

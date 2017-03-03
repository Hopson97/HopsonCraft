#ifndef CPOSITION_H_INCLUDED
#define CPOSITION_H_INCLUDED

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

#endif // CPOSITION_H_INCLUDED

#include "Chunk_Location.h"

Chunk_Location :: Chunk_Location (int32_t x, int32_t z)
:   x   (x)
,   z   (z)
{}

bool Chunk_Location::operator== (const Chunk_Location& other) const
{
    return (x == other.x) && (z == other.z);
}


bool Chunk_Location::operator!= (const Chunk_Location& other) const
{
    return !((x == other.x) && (z == other.z));
}

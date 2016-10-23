#include "Chunk_Position.h"

Chunk_Position::Chunk_Position(int x, int z)
:   x   (x)
,   z   (z)
{ }

bool Chunk_Position::operator == (const Chunk_Position& other)
{
    return (x == other.x) && (z == other.z);
}

bool Chunk_Position::operator != (const Chunk_Position& other)
{
    return (x != other.x) || (z != other.z);
}

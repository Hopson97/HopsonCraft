#include "Block_Location.h"

#include "../../Util/Random.h"
#include "../World.h"

Block_Location::Block_Location (int x, int y, int z)
:   x   (x)
,   y   (y)
,   z   (z)
{}

bool Block_Location::operator== (const Block_Location& other) const
{
    return  (x == other.x) &&
            (y == other.y) &&
            (z == other.z);
}


bool Block_Location::operator!= (const Block_Location& other) const
{
    return  (x != other.x) &&
            (y != other.y) &&
            (z != other.z);
}

Block_Location Block_Location::getRandom(int maxY)
{
    return
    {
        Random::integer(0, World_Constants::CHUNK_SIZE - 1),
        Random::integer(0, maxY),
        Random::integer(0, World_Constants::CHUNK_SIZE - 1)
    };
}

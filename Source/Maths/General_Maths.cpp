#include "General_Maths.h"

#include "../World/World_Constants.h"

#include <cmath>

namespace Maths
{
    Chunk::Position worldToChunkPos(const Vector3& position)
    {
        return  {(double)((int)position.x / World_Constants::CH_SIZE),
                 (double)((int)position.z / World_Constants::CH_SIZE)};
    }

    Block::Column_Position worldToBlockPos(const Vector3& position)
    {
        int32_t x = (int32_t) position.x % World_Constants::CH_SIZE;
        int32_t z = (int32_t) position.z % World_Constants::CH_SIZE;

        return  {x, (int32_t)position.y, z};
    }

}

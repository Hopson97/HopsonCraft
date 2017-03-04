#include "General_Maths.h"

#include "../World/World_Constants.h"

#include <cmath>

namespace Maths
{
    Chunk::Position worldToChunkPos(const Vector3& position)
    {
        return  {(int)std::floor(position.x / World_Constants::CH_SIZE),
                 (int)std::floor(position.z / World_Constants::CH_SIZE)};
    }
}

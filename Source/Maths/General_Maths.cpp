#include "General_Maths.h"

#include "../World/World_Constants.h"

#include <cmath>

namespace Maths
{

    Chunk::Position worldToChunkPos(const Vector3& position)
    {
        return  {(int32_t)position.x >> CHUNK_SIZE_LOG2,
                 (int32_t)position.z >> CHUNK_SIZE_LOG2};
    }

    Block::Column_Position worldToBlockPos(const Vector3& position)
    {
        return  {(int32_t) position.x % CHUNK_SIZE,
                 (int32_t) position.y,
                 (int32_t) position.z % CHUNK_SIZE};
    }

}

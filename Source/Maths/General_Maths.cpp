#include "General_Maths.h"

#include "../World/World_Constants.h"

#include <cmath>

namespace Maths
{

    Chunk::Chunklet_Position worldToChunkletPos(const Vector3& position)
    {
        auto fullChunk = worldToChunkPos(position);
        auto yIndex  = position.y / CHUNK_SIZE;

        return {fullChunk.x, yIndex, fullChunk.y};
    }


    Chunk::Position worldToChunkPos(const Vector3& position)
    {
        return  {(int32_t)position.x / CHUNK_SIZE,
                 (int32_t)position.z / CHUNK_SIZE};
    }

    Block::Position worldToBlockPos(const Vector3& position)
    {
        return  {(int32_t) position.x % CHUNK_SIZE,
                 (int32_t) position.y,
                 (int32_t) position.z % CHUNK_SIZE};
    }

    Block::Small_Position blockToSmallBlockPos(const Block::Position& position)
    {
        int32_t y = position.y % CHUNK_SIZE;
        return
        {
            (int8_t) position.x,
            (int8_t) y,
            (int8_t) position.z,
        };
    }

}

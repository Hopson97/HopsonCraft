#include "Position_Conversion.h"

#include "../World/World_Constants.h"

#include <cmath>

namespace Maths {
namespace Convert
{

    Chunk::Chunklet_Position worldToChunkletPosition (const Vector3& position)
    {
        auto fullChunk = worldToChunkPosition(position);
        auto yIndex  = position.y / CHUNK_SIZE;

        return {fullChunk.x, (int)yIndex, fullChunk.y};
    }

    Chunk::Position worldToChunkPosition (const Vector3& position)
    {
        return  {(int)position.x / CHUNK_SIZE,
                 (int)position.z / CHUNK_SIZE};
    }

    Block::Position worldToChunkBlockPosition (const Vector3& position)
    {
        return  {(int) position.x % CHUNK_SIZE,
                 (int) position.y,
                 (int) position.z % CHUNK_SIZE};
    }

    Block::Position chunkBlockToSectionBlockPosition (const Block::Position& position)
    {
        int y = position.y % CHUNK_SIZE;
        return
        {
            position.x,
            y,
            position.z,
        };
    }

    Block::Position chunkBlockToWorldBlockPosition (const Block::Position& blockPosition,
                                                    const Chunk::Position& chunkPosition)
    {
        return
        {
            blockPosition.x + chunkPosition.x * CHUNK_SIZE,
            blockPosition.y,
            blockPosition.z + chunkPosition.y * CHUNK_SIZE,
        };
    }

    Block::Position sectionBlockToWorldBlockPosition (const Block::Position&          blockPosition,
                                                      const Chunk::Chunklet_Position& chunkPosition)
    {
        return
        {
            blockPosition.x + chunkPosition.x * CHUNK_SIZE,
            blockPosition.y + chunkPosition.y * CHUNK_SIZE,
            blockPosition.z + chunkPosition.z * CHUNK_SIZE,
        };
    }
}
}

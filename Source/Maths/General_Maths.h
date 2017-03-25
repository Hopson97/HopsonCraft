#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/CPosition.h"
#include "../World/Block/Block_Position.h"

namespace Maths
{
    Chunk::Chunklet_Position worldToChunkletPos (const Vector3& position);
    Chunk::Position worldToChunkPos             (const Vector3& position);

    Block::Position worldToBlockPos             (const Vector3& position);
    Block::Small_Position   blockToSmallBlockPos(const Block::Position& position);
}

#endif // GENERAL_MATHS_H_INCLUDED


/*
namespace Maths
{
    Chunk::Position worldToChunkPos(const Vector3& position)
    {
        return  Chunk::Position(std::floor(position.x / World_Constants::CH_SIZE),
                                std::floor(position.z / World_Constants::CH_SIZE));
    }

    Block::Column_Position worldToBlockPos(const Vector3& position)
    {
        int32_t x = (int32_t) position.x % World_Constants::CH_SIZE;
        int32_t z = (int32_t) position.z % World_Constants::CH_SIZE;

        return  {x, (int32_t)position.y, z};
    }

}
*/

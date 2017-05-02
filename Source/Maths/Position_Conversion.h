#ifndef POSITION_CONVERSION_H_INCLUDED
#define POSITION_CONVERSION_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/CPosition.h"
#include "../World/Block/Block_Position.h"

namespace Maths
{
    Chunk::Chunklet_Position worldToChunkletPos (const Vector3& position);
    Chunk::Position worldToChunkPos             (const Vector3& position);

    Block::Small_Position worldToSmallBlockPos  (const Vector3& position);
    Block::Position worldToBlockPos             (const Vector3& position);
    Block::Small_Position   blockToSmallBlockPos(const Block::Position& position);
}

#endif // POSITION_CONVERSION_H_INCLUDED

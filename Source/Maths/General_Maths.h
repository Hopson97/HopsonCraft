#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/CPosition.h"
#include "../World/Block/Block_Position.h"

namespace Maths
{
    Chunk::Position         worldToChunkPos(const Vector3& position);
    Block::Column_Position  worldToBlockPos(const Vector3& position);
}

#endif // GENERAL_MATHS_H_INCLUDED

#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/CPosition.h"

namespace Maths
{
    Chunk::Position worldToChunkPos(const Vector3& position);
}

#endif // GENERAL_MATHS_H_INCLUDED

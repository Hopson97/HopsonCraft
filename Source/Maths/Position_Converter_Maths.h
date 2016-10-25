#ifndef POSITION_CONVERTER_MATHS_H_INCLUDED
#define POSITION_CONVERTER_MATHS_H_INCLUDED

#include "Chunk_Location.h"
#include "OpenGL/GLM/glm_transformations.h"

namespace Maths
{
    Vector3 worldToBlockPosition(const Vector3& worldPosition);

    Chunk_Location worldToChunkPosition(const Vector3& worldPosition);

    unsigned getChunkDistance (const Chunk_Location& l1, const Chunk_Location& l2);
}

#endif // POSITION_CONVERTER_MATHS_H_INCLUDED

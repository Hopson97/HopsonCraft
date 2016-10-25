#ifndef POSITION_CONVERTER_MATHS_H_INCLUDED
#define POSITION_CONVERTER_MATHS_H_INCLUDED

#include "Chunk_Location.h"
#include "OpenGL/GLM/glm_transformations.h"

namespace Maths
{
    Vector3 worldToBlockPosition(const Vector3& worldPosition);

    Chunk_Location worldToChunkPosition(const Vector3& worldPosition);
}

#endif // POSITION_CONVERTER_MATHS_H_INCLUDED

#ifndef POSITION_CONVERTER_MATHS_H_INCLUDED
#define POSITION_CONVERTER_MATHS_H_INCLUDED

#include "Chunk/Chunk_Location.h"
#include "OpenGL/GLM/glm_transformations.h"
#include "Block_Location.h"

namespace Maths
{
    Block_Location worldToBlockPosition(const Vector3& worldPosition);

    Chunk_Location worldToChunkPosition(const Vector3& worldPosition);

    unsigned getChunkDistance (const Chunk_Location& l1, const Chunk_Location& l2);

    Vector3 chunkBlockToWorldCoords(const Block_Location& bLocation,
                                    const Chunk_Location& cLocation);
}

#endif // POSITION_CONVERTER_MATHS_H_INCLUDED

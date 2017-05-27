#ifndef POSITION_CONVERSION_H_INCLUDED
#define POSITION_CONVERSION_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/Position.h"
#include "../World/Block/Block_Position.h"

namespace Maths {
namespace Convert
{
    Chunk::Chunklet_Position    worldToChunkletPosition      (const Vector3& position);
    Chunk::Position             worldToChunkPosition         (const Vector3& position);

    Block::Position worldToSectionBlockPosition         (const Vector3& position);
    Block::Position worldToChunkBlockPosition           (const Vector3& position);
    Block::Position chunkBlockToSectionBlockPosition    (const Block::Position& position);

    Block::Position chunkBlockToWorldBlockPosition      (const Block::Position& blockPosition,
                                                         const Chunk::Position& chunkPosition);

    Block::Position sectionBlockToWorldBlockPosition    (const Block::Position&          blockPosition,
                                                         const Chunk::Chunklet_Position& chunkPosition);
}
}

#endif // POSITION_CONVERSION_H_INCLUDED

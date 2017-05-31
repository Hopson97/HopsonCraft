#include "FullChunk.h"

#include "../WorldConstants.h"

namespace Chunk
{
    int64_t FullChunk::getX() const
    {
        return m_xPosition;
    }

    int64_t FullChunk::getZ() const
    {
        return m_zPosition;
    }

    Section* FullChunk::getSection(int64_t blockY)
    {
        auto index = blockY / CHUNK_SIZE;

        return (index < 0) || (index >= m_sections.size()) ?
            nullptr :
            &m_sections[index];
    }

}

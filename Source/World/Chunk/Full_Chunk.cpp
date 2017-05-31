#include "Full_Chunk.h"

#include "../World_Constants.h"

namespace Chunk
{
    int64_t Full_Chunk::getX() const
    {
        return m_xPosition;
    }

    int64_t Full_Chunk::getZ() const
    {
        return m_zPosition;
    }

    Section* Full_Chunk::getSection(int64_t blockY)
    {
        auto index = blockY / CHUNK_SIZE;

        return (index < 0) || (index >= m_sections.size()) ?
            nullptr :
            &m_sections[index];
    }

}

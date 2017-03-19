#include "CMap.h"

namespace Chunk
{
    Section* Map::get(const Chunk::Position& position)
    {
        if (existsAt(position))
            return m_chunks[position].get();
        else
            return nullptr;
    }

    bool Map::existsAt(const Chunk::Position& position)
    {
        return m_chunks.find(position) != m_chunks.end();
    }

}

#include "CMap.h"

namespace Chunk
{
    void Map::addChunk(const Chunk::Position& position, World& world)
    {
        m_chunks.insert(std::make_pair((position),
                        std::make_unique<Full_Chunk>(world, *this, position)));
    }

    Section* Map::get(const Chunk::Chunklet_Position& position)
    {
        Position chunkPos (position.x, position.z);
        return existsAt(position) ?
            m_chunks.at(chunkPos)->getSection(position.y) :
            nullptr;
    }

    bool Map::existsAt(const Chunk::Chunklet_Position& position)
    {
        Position chunkPos(position.x, position.z);
        return m_chunks.find(chunkPos) != m_chunks.end();
    }
}

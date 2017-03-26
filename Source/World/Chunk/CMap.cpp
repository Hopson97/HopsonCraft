#include "CMap.h"

namespace Chunk
{
    Map::Map(int32_t renderDistance)
    :   m_currRenderDistance    (renderDistance)
    ,   m_chunksVector          (renderDistance * renderDistance)
    { }

    int32_t Map::getIndex(const Chunk::Position& position)
    {
        return position.x * m_currRenderDistance + position.y;
    }

    void Map::addChunk(const Chunk::Position& position, World& world)
    {
        //m_chunks.emplace(position, );
        m_chunksVector[getIndex(position)] = std::move(Full_Chunk{world, *this, position});
    }

    Section* Map::get(const Chunk::Chunklet_Position& position)
    {
        Position chunkPos (position.x, position.z);
        if (existsAt(chunkPos))
        {
            return m_chunksVector[getIndex(chunkPos)].getSection(position.y);
        }
        else
            return nullptr;
    }

    Full_Chunk* Map::get(const Chunk::Position& position)
    {
        if (existsAt(position))
        {
            return &m_chunksVector[getIndex(position)];
        }
        else
            return nullptr;
    }

    bool Map::existsAt(const Chunk::Position& position)
    {
        if (position.x < 0) return false;
        if (position.x > m_currRenderDistance - 1) return false;
        if (position.y < 0) return false;
        if (position.y > m_currRenderDistance - 1) return false;
        return true;
    }

}

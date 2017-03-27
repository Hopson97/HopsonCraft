#include "CMap.h"

#include <iostream>

namespace Chunk
{
    Map::Map()
    {
        m_chunks = (Full_Chunk*) malloc (sizeof(Full_Chunk));
    }

    Map::~Map()
    {
        free(m_chunks);
    }


    void Map::addChunk(const Chunk::Position& position, World& world)
    {
        m_chunksMap.insert(std::make_pair(position, std::move(Full_Chunk{world, *this, position})));
    }

    Section* Map::get(const Chunk::Chunklet_Position& position)
    {
        Position chunkPos (position.x, position.z);
        if (existsAt(chunkPos))
        {
            return m_chunksMap[chunkPos].getSection(position.y);
        }
        else
            return nullptr;
    }

    Full_Chunk* Map::get(const Chunk::Position& position)
    {
        if (existsAt(position))
        {
            return &m_chunksMap[position];
        }
        else
            return nullptr;
    }

    bool Map::existsAt(const Chunk::Position& position)
    {
        return m_chunksMap.find(position) != m_chunksMap.end();
    }

}

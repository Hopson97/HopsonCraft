#include "CMap.h"

#include <iostream>

#include "../World.h"

namespace Chunk
{
    void Map::addChunk(const Chunk::Position& position, World& world, bool populateBlocks)
    {
        mp_world = &world;

        if (existsAt(position))
        {
            get(position)->generateBlocks(world.getWorldSettings());
        }
        else
        {
            m_chunksMap.emplace(std::piecewise_construct,
                                std::forward_as_tuple(position),
                                std::forward_as_tuple(world,
                                                      *this,
                                                      position,
                                                      world.getWorldSettings(),
                                                      populateBlocks));
        }
    }

    Section* Map::get(const Chunk::Chunklet_Position& position)
    {
        Position chunkPos (position.x, position.z);
        if (existsAt(chunkPos))
        {
            return m_chunksMap[chunkPos].getSection(position.y);
        }
        else
        {
            std::cout << "A false return\n";
            addChunk(chunkPos, *mp_world, false);
            return m_chunksMap[chunkPos].getSection(position.y);
        }
    }

    Full_Chunk* Map::get(const Chunk::Position& position)
    {
        if (existsAt(position))
        {
            return &m_chunksMap[position];
        }
        else
        {
            addChunk(position, *mp_world, false);
            return &m_chunksMap[position];
        }
    }

    bool Map::existsAt(const Chunk::Position& position) const
    {
        return m_chunksMap.find(position) != m_chunksMap.end();
    }

    std::unordered_map<Position, Full_Chunk>& Map::getChunks()
    {
        return m_chunksMap;
    }
}

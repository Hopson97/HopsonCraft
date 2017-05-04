#include "CMap.h"

#include <iostream>

#include "../World.h"

namespace Chunk
{
    Map::Map(World& world)
    :   mp_world    (&world)
    { }

    void Map::addChunk(std::unordered_map<Position, Full_Chunk>& map,
                       const Chunk::Position& position,
                       bool populateBlocks)
    {
        map.emplace(std::piecewise_construct,
                    std::forward_as_tuple(position),
                    std::forward_as_tuple(*mp_world,
                                        *this,
                                        position,
                                        mp_world->getWorldSettings(),
                                        populateBlocks));
    }


    void Map::addChunk(const Chunk::Position& position, bool populateBlocks)
    {
        if (existsAt(position))
        {
            get(position)->generateBlocks(mp_world->getWorldSettings());
        }
        else
        {
            addChunk(m_chunksMap, position, populateBlocks);
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
            return nullptr;
            //addChunk(chunkPos, false);
            //return m_chunksMap[chunkPos].getSection(position.y);
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
            return nullptr;
            //addChunk(position, false);
            //return &m_chunksMap[position];
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

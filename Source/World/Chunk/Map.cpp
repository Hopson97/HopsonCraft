#include "Map.h"

#include <iostream>

#include "../World.h"

#include "../../Util/STD_Util.h"

namespace Chunk
{
    Map::Map(World& world)
    :   m_pWorld            (&world)
    ,   m_chunkGenerator    (world.getWorldSettings())
    { }

    void Map::addChunk(std::unordered_map<Position, Full_Chunk>& map,
                       const Chunk::Position& position,
                       bool populateBlocks)
    {
        map.emplace(std::piecewise_construct,
                    std::forward_as_tuple(position),
                    std::forward_as_tuple(*m_pWorld,
                                        *this,
                                        position,
                                        m_pWorld->getWorldSettings(),
                                        m_pWorld->getWorldFile()));

        if (populateBlocks)
        {
            m_chunkGenerator.generateBlocksFor(map[position], m_pWorld->getWorldFile());
        }
    }


    void Map::deleteChunk(const Chunk::Position& position, World_File& worldFile)
    {
        m_tempChunks.erase(position);
        m_chunksMap .erase(position);
    }


    void Map::addChunk(const Chunk::Position& position, bool populateBlocks)
    {
        if (existsInMap(m_tempChunks, position))
        {
            m_chunkGenerator.generateBlocksFor(m_tempChunks[position], m_pWorld->getWorldFile());
            m_chunksMap.emplace(position, std::move(m_tempChunks[position]));
            m_tempChunks.erase(position);
        }
        else if (!existsAt(position))
        {
            addChunk(m_chunksMap, position, populateBlocks);
        }
    }

    const Full_Chunk* Map::get(const Chunk::Position& position) const
    {
        return existsAt(position) ?
            &m_chunksMap.at(position) :
            nullptr;
    }

    const Section* Map::get(const Chunk::Chunklet_Position& position) const
    {
        return existsAt({position.x, position.z}) ?
            m_chunksMap.at({position.x, position.z}).getSection(position.y) :
            nullptr;
    }


    Section* Map::editableGet(const Chunk::Chunklet_Position& position)
    {
        Position chunkPos (position.x, position.z);
        if (existsAt(chunkPos))
        {
            return m_chunksMap[chunkPos].editableGetSection(position.y);
        }
        else
        {
            addChunk(m_tempChunks, chunkPos, false);
            return m_tempChunks[chunkPos].editableGetSection(position.y);
        }
    }

    Full_Chunk& Map::editableGet(const Chunk::Position& position)
    {
        if (existsAt(position))
        {
            return m_chunksMap[position];
        }
        else
        {
            addChunk(m_tempChunks, position, false);
            return m_tempChunks[position];
        }
    }

    bool Map::existsAt(const Chunk::Position& position) const
    {
        return existsInMap(m_chunksMap, position);
    }

    std::unordered_map<Position, Full_Chunk>& Map::getChunks()
    {
        return m_chunksMap;
    }
}

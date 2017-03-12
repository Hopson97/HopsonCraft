#include "CColumn.h"

#include <SFML/System/Clock.hpp>
#include <cmath>

#include "CRegenerator.h"

#include "../../Renderer/RMaster.h"
#include "../../Util/Random.h"

#include <iostream>



namespace Chunk
{
    Column::Column(const Position& pos, Map& map, Regenerator& regenerator, World_File& file)
    :   m_position      (pos)
    ,   m_p_chunkMap    (&map)
    ,   m_p_regenerator (&regenerator)
    ,   m_p_worldFile   (&file)
    {
        minX = {pos.x, 0, pos.y, 0};

        Noise::Generator noise1;
        std::vector<int32_t> heightMap(World_Constants::CH_AREA);

        int v;
        noise1.setSeed(33775);

        //noise1.setNoiseFunction({10, 70, 0.65, 480, 0});
        //noise1.setNoiseFunction({10, 90, 0.1, 580, 0});

        //noise1.setNoiseFunction({8, 80, 0.53, 200, 0});
        noise1.setNoiseFunction({10, 65, 0.535, 280, 0});

        if( pos.x < 0 || pos.y < 0)
        {
            v = 75;
        }
        else
        {
            for (int32_t x = 0; x < World_Constants::CH_SIZE; x++)
            {
                for (int32_t z = 0; z < World_Constants::CH_SIZE; z++)
                {
                    double h = noise1.getValue(x, z, pos.x, pos.y);
                    heightMap[x * World_Constants::CH_SIZE + z] = h;
                }
            }
            v = *std::max_element(heightMap.begin(), heightMap.end());
        }

        if (v < 75) v = 75;

        for (int32_t y = 0; y < v + 1; y++)
        {
            for (int32_t x = 0; x < World_Constants::CH_SIZE; x++)
            {
                for (int32_t z = 0; z < World_Constants::CH_SIZE; z++)
                {
                    int h = heightMap[x * World_Constants::CH_SIZE + z];


                    if (y == h)
                    {
                        y > 73?
                            setBlock({x, y, z}, Block::ID::Grass) :
                            setBlock({x, y, z}, Block::ID::Sand);
                    }
                    else if ( y < 73 && y > h)
                    {
                        setBlock({x, y, z}, Block::ID::Water);
                    }
                    else if (y < h && y > h - 3 )
                    {
                        setBlock({x, y, z}, Block::ID::Dirt);
                    }
                    else if (y <= h - 3)
                    {
                        setBlock({x, y, z}, Block::ID::Stone);
                    }
                }
            }
        }
        for (auto& c : m_chunklets)
        {
            Chunklet& ch = *c;
            ch.load(file);
        }

        m_flags.generated = true;
    }

    void Column::createFullMesh()
    {
        for (auto& c : m_chunklets)
        {
            c->createMesh();
        }
        m_flags.hasFullMesh = true;
    }


    void Column::setBlock(const Block::Column_Position& pos, CBlock block)
    {
        auto trueLocation       = getChunkletBlockLocation(pos);
        int32_t chunkletIndex   = trueLocation.first;
        int32_t blockYPosition  = trueLocation.second;

        while (chunkletIndex + 1 > m_chunkCount)
        {
            addChunklet();
        }
        Chunklet* chunk = getChunkletnc(chunkletIndex);

        Block::Small_Position blockPosition (pos.x, blockYPosition, pos.z);

        chunk->qSetBlock(blockPosition, block);

        if(m_flags.generated)
        {
            m_p_regenerator->addChunklets(chunk->setBlock(blockPosition, block));
        }
        else
        {
            chunk->qSetBlock(blockPosition, block);
        }

    }

    CBlock Column::getBlock(const Block::Column_Position& pos) const
    {
        if(pos.y < 0)
        {
            return Block::ID::Air;
        }
        auto trueLocation       = getChunkletBlockLocation(pos);
        int32_t chunkletIndex   = trueLocation.first;
        int32_t blockYPosition  = trueLocation.second;

        if (chunkletIndex < m_chunkCount && chunkletIndex >= 0)
        {
            Block::Small_Position bp (pos.x, blockYPosition, pos.z);
            return m_chunklets.at(chunkletIndex)->qGetBlock(bp);
        }
        else
        {
            return Block::ID::Air;
        }
    }

    std::pair<int32_t, int32_t> Column::getChunkletBlockLocation(const Block::Column_Position& pos) const
    {
        auto yIndex = std::ceil(pos.y / World_Constants::CH_SIZE);
        auto yPos = pos.y - World_Constants::CH_SIZE * yIndex;

        return std::make_pair(yIndex, yPos);
    }


    Chunklet* Column::getChunklet(int32_t index)
    {
        if (index > m_chunkCount - 1)
        {
            return nullptr;
        }
        else if (index < 0)
        {
            return nullptr;
        }
        return m_chunklets.at(index).get();
    }

    Chunklet* Column::getChunkletnc(int32_t index)
    {
        if (index > m_chunkCount - 1)
        {
            return nullptr;
        }
        else if (index < 0)
        {
            return nullptr;
        }
        return m_chunklets.at(index).get();
    }


    const Position& Column::getPosition () const
    {
        return m_position;
    }

    const Column::CFlags& Column::getFlags ()
    {
        return m_flags;
    }

    void Column::setDeleteFlag (bool deleteF)
    {
        m_flags.deleteMe = deleteF;
/*
        for (auto& c : m_chunklets)
        {
            Chunklet& ch = *c;
            ch.save(*m_p_worldFile);
        }
*/
    }

    void Column::update()
    {

    }

    void Column::draw(Renderer::Master& renderer)
    {
        for(auto itr = m_chunklets.begin(); itr != m_chunklets.end();)
        {
            Chunklet& chunklet = *(*itr);
            if (chunklet.getFlags().hasFaces)
            {
                if (chunklet.getFlags().hasBuffered)
                {
                    renderer.draw(chunklet);
                    ++itr;
                }
                else
                {
                    chunklet.bufferMesh();
                }
            }
            else
            {
                ++itr;
            }
        }
    }

    void Column::addChunklet()
    {
        m_chunklets.push_back(std::make_unique<Chunklet>
                              (Chunklet_Position(m_position.x,
                                                 m_chunkCount++,
                                                 m_position.y),
                               *m_p_chunkMap));

        maxX = {minX.x          + World_Constants::CH_SIZE,
                m_chunkCount    * World_Constants::CH_SIZE,
                minX.z          + World_Constants::CH_SIZE,
                0};
    }


}

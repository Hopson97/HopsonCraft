#include "Chunk_Generator.h"

#include <iostream>

#include "../../Util/Hasher.h"
#include "../../Maths/General_Maths.h"

#include "../World_Settings.h"
#include "../Chunk/CFull_Chunk.h"

#include "GStructures.h"


Chunk_Generator::Chunk_Generator(const World_Settings& worldSettings)
:   m_pWorldSettings    (&worldSettings)
{
    m_noiseGenerator.setSeed            (worldSettings.seed);
    m_noiseGenerator.setNoiseFunction   (worldSettings.noiseData);

    //m_biomeNoise.setSeed            (worldSettings.seed);
    //m_biomeNoise.setNoiseFunction   ({5, 100, 0.4, 450});
}

void Chunk_Generator::reset()
{
    m_maxHeight = 0;
    m_heightMap.reset();
    //m_biomeMap.reset();
    m_oakTreeLocations.clear();
}


void Chunk_Generator::generateBlocksFor(Chunk::Full_Chunk& chunk)
{
    m_genMutex.lock();

    m_pChunk = &chunk;

    reset();
    setRandomSeed();
    makeBiomeMap();
    makeHeightMap();


    m_maxHeight = std::max(m_maxHeight, WATER_LEVEL);

    for (int y = 0; y < m_maxHeight + 1; ++y)
    {
        for (int x = 0; x < CHUNK_SIZE; ++x)
        {
            for (int z = 0; z < CHUNK_SIZE; ++z)
            {
                auto block = getBlock({x, y, z});
                if (block != Block::ID::Air)
                {
                    chunk.qSetBlock({x, y, z}, block);
                }
            }
        }
    }

    //Make trees
    for (auto& pos : m_oakTreeLocations)
    {
        makeOakTree(*m_pChunk, pos, m_randomGenerator);
    }

    chunk.hasGeneratedBlockData = true;
    m_genMutex.unlock();
}

Block::ID Chunk_Generator::getBlock(const Block::Position& pos)
{
    auto blockID    = Block::ID::Air;
    int heightHere  = m_heightMap.at(pos.x, pos.z);
    int y           = pos.y;

    if (y > heightHere)
    {
        if (y > WATER_LEVEL)
            return Block::ID::Air;
        else
            blockID = Block::ID::Water;
    }
    else if (y == heightHere)
    {
        setTopBlock(pos, blockID);
    }
    else if (Maths::inRange(y, heightHere - 3, heightHere))
    {
        blockID = Block::ID::Dirt;
    }
    else if (y <= heightHere - 4)
    {
        blockID = Block::ID::Stone;
    }

    return blockID;
}

void Chunk_Generator::setTopBlock(const Block::Position& pos, Block::ID& blockID)
{
    auto y = pos.y;

    if (y >= WATER_LEVEL)   //Above water
    {
        if (y <= BEACH_LEVEL)   //Beach
        {
            blockID = Block::ID::Sand;
        }
        else    //Ground blocks
        {
            //int biome = m_biomeMap.at(pos.x, pos.z);

            blockID = Block::ID::Grass;
            if (m_randomGenerator.intInRange(0, 110) == 5)
            {
                    m_oakTreeLocations.push_back(pos);
            }
        }
    }
    else //Underwater
    {
        blockID = m_randomGenerator.intInRange(0, 5) > 1 ?
            Block::ID::Sand :
            Block::ID::Dirt;
    }
}


void Chunk_Generator::setRandomSeed()
{
    m_randomGenerator.setSeed(Hasher::hash((int32_t)m_pWorldSettings->seed,
                                           m_pChunk->getPosition().x,
                                           m_pChunk->getPosition().y));
}

void Chunk_Generator::makeHeightMap()
{
    for (int32_t x = 0 ; x < CHUNK_SIZE; ++x)
    {
        for (int32_t z = 0 ; z < CHUNK_SIZE; ++z)
        {
            int32_t height =
                m_noiseGenerator.getValue(x, z,
                                          m_pChunk->getPosition().x + 3,
                                          m_pChunk->getPosition().y + 3);
            m_heightMap.at(x, z) = height;
            m_maxHeight = std::max(m_maxHeight, height);
        }
    }
}

void Chunk_Generator::makeBiomeMap()
{
    /*
    for (int32_t x = 0 ; x < CHUNK_SIZE; ++x)
    {
        for (int32_t z = 0 ; z < CHUNK_SIZE; ++z)
        {
            int32_t height =
                m_biomeNoise.getValue(x, z,
                                      m_pChunk->getPosition().x + 3,
                                      m_pChunk->getPosition().y + 3);
            m_biomeMap.at(x, z) = height;
        }
    }
    */
}


#include "Chunk_Generator.h"

#include <iostream>

#include "../../Util/Hasher.h"
#include "../../Maths/General_Maths.h"

#include "../World_Settings.h"
#include "../Chunk/CFull_Chunk.h"

#include "GTrees.h"

namespace
{
    enum Biome
    {
        Grassland,
        Forest,
        Mountains
    };

    Biome getBiome(int val)
    {
        if (val > 140)
        {
            return Grassland;
        }
        else if (Maths::inRange(val, 120, 140))
        {
            return Mountains;
        }
        else
        {
            return Forest;
        }
    }

    Noise::Data getBiomeNoise (Biome b)
    {
        switch(b)
        {
            case Biome::Forest:
                return {7, 100, 0.52, 230  -10 };

            case Biome::Grassland:
                return {7, 85, 0.51, 235, -15 };

            case Biome::Mountains:
                return {8, 550, 0.50, 283, -395 };
        }
    }

}


Chunk_Generator::Chunk_Generator(const World_Settings& worldSettings)
:   m_pWorldSettings    (&worldSettings)
{
    m_noiseGenerator.setSeed            (worldSettings.seed);
    m_noiseGenerator.setNoiseFunction   (worldSettings.noiseData);

    m_biomeNoise.setSeed            (worldSettings.seed);
    m_biomeNoise.setNoiseFunction   ({6, 112, 0.5, 200});
}

void Chunk_Generator::reset()
{
    m_maxHeight = 0;
    m_heightMap.reset();
    m_biomeMap.reset();
    m_oakTreeLocations.clear();
    m_littleBlockLoc.clear();
}


void Chunk_Generator::generateBlocksFor(Chunk::Full_Chunk& chunk)
{
    //Only one chunk can generate a time smh
    m_genMutex.lock();

    m_pChunk = &chunk;
    reset();

    //Makes a superflat world
    if (m_pWorldSettings->isSuperFlat)
    {
        makeSuperFlatWorld();
        m_genMutex.unlock();
        return;
    }
    else
    {
        makeRegularWorld();
    }

    chunk.setHasGeneratedFlag();
    m_genMutex.unlock();
}

void Chunk_Generator::makeSuperFlatWorld()
{
    for (int y = 0; y < CHUNK_SIZE; ++y)
    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int z = 0; z < CHUNK_SIZE; ++z)
    {
        Block::ID block = Block::ID::Grass;
        if (y == CHUNK_SIZE - 1)
        {
            block = Block::ID::Grass;
        }
        else if (Maths::inRange(y, 12, 15))
        {
            block = Block::ID::Dirt;
        }
        else
        {
            block = Block::ID::Stone;
        }

        m_pChunk->qSetBlock({x, y, z}, block);
    }
    m_pChunk->setHasGeneratedFlag();
}

void Chunk_Generator::makeRegularWorld()
{
    setRandomSeed   ();
    makeBiomeMap    ();

    m_pWorldSettings->isExperimentalMode ?
            makeAdvancedHeigtMap() :
            makeHeightMap();

    m_maxHeight = std::max(m_maxHeight, WATER_LEVEL);

    for (int y = 0; y < m_maxHeight + 1; ++y)
    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int z = 0; z < CHUNK_SIZE; ++z)
    {
        auto block = getBlock({x, y, z});
        if (block != Block::ID::Air)
        {
            m_pChunk->qSetBlock({x, y, z}, block);
        }
    }

    for (auto& pos : m_littleBlockLoc)
    {
        m_pChunk->qSetBlock({pos.first.x, pos.first.y + 1, pos.first.z}, pos.second);
    }

    for (auto& pos : m_oakTreeLocations)
    {
        makeOakTree(*m_pChunk, pos, m_randomGenerator);
    }
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
    int biome = m_biomeMap.at(pos.x, pos.z);

    Biome biomeType = getBiome(biome);

    if (y >= WATER_LEVEL)   //Above water
    {
        if (y <= BEACH_LEVEL)   //Beach
        {
            blockID = Block::ID::Sand;
        }
        else //Ground blocks
        {
            switch (biomeType)
            {
                case Grassland:
                    blockID = Block::ID::Grass;
                    if (m_randomGenerator.intInRange(0, 350) == 5)
                    {
                        m_oakTreeLocations.push_back(pos);
                    }
                    if (m_randomGenerator.intInRange(0, 200) < 5)
                    {
                        m_littleBlockLoc.push_back(std::make_pair(pos,
                                                                  Block::ID::Rose));
                    }
                    if (m_randomGenerator.intInRange(0, 30) < 5)
                    {
                        m_littleBlockLoc.push_back(std::make_pair(pos,
                                                                  Block::ID::Tall_Grass));
                        if (m_randomGenerator.intInRange(0, 5) < 2)
                        m_littleBlockLoc.push_back(std::make_pair(Block::Position{pos.x, pos.y + 1, pos.z},
                                                                  Block::ID::Tall_Grass));
                    }
                    break;

                case Mountains:
                    //blockID = Block::ID::Stone;
                   // break;
                case Forest:
                    blockID = m_randomGenerator.intInRange(0, 10) <= 7 ?
                        Block::ID::Grass :
                        Block::ID::Dirt;
                    if (m_randomGenerator.intInRange(0, 50) == 5)
                    {
                        m_oakTreeLocations.push_back(pos);
                    }
                    if (m_randomGenerator.intInRange(0, 250) < 5)
                    {
                        m_littleBlockLoc.push_back(std::make_pair(pos,
                                                                  Block::ID::Rose));
                    }
                    if (m_randomGenerator.intInRange(0, 145) < 5)
                    {
                        m_littleBlockLoc.push_back(std::make_pair(pos,
                                                                  Block::ID::Tall_Grass));
                    }
                    break;
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
    for (int32_t z = 0 ; z < CHUNK_SIZE; ++z)
    {
        int32_t height =
            m_noiseGenerator.getValue(x, z,
                                    m_pChunk->getPosition().x,
                                    m_pChunk->getPosition().y);
        m_heightMap.at(x, z) = height;
        m_maxHeight = std::max(m_maxHeight, height);
    }
}

//This uses interpolation to um interpolate between values rather
//than using noise function on every point.
void Chunk_Generator::makeAdvancedHeigtMap()
{
    static auto edge = CHUNK_SIZE;

    int q11 = m_noiseGenerator.getValue( 0, 0,
                                        m_pChunk->getPosition().x,
                                        m_pChunk->getPosition().y);
    int q21 = m_noiseGenerator.getValue( 0, 0,
                                        m_pChunk->getPosition().x + 1,
                                        m_pChunk->getPosition().y);

    int q12 = m_noiseGenerator.getValue( 0, 0,
                                        m_pChunk->getPosition().x,
                                        m_pChunk->getPosition().y + 1);

    int q22 = m_noiseGenerator.getValue( 0, 0,
                                        m_pChunk->getPosition().x + 1,
                                        m_pChunk->getPosition().y + 1);
    for (int32_t x = 0 ; x < CHUNK_SIZE; ++x)
    for (int32_t z = 0 ; z < CHUNK_SIZE; ++z)
    {
        int height =
            Maths::bilinearInterpolate(q11, q12, q21, q22, 0, edge, 0, edge, x, z);

        m_heightMap.at(x, z) = height;
        m_maxHeight = std::max(m_maxHeight, height);
    }
}

void Chunk_Generator::makeBiomeMap()
{
    for (int32_t x = 0 ; x < CHUNK_SIZE + 1; ++x)
    for (int32_t z = 0 ; z < CHUNK_SIZE + 1; ++z)
    {
        int32_t height =
            m_biomeNoise.getValue(x, z,
                                m_pChunk->getPosition().x,
                                m_pChunk->getPosition().y);
        m_biomeMap.at(x, z) = height;
    }
}


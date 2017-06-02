#include "Terrain_Generator.h"

#include <iostream>

#include "../../Util/Hasher.h"
#include "../../Maths/General_Maths.h"

#include "../World_Settings.h"
#include "../Chunk/Full_Chunk.h"

#include "Structures.h"

Terrain_Generator::Terrain_Generator(const World_Settings& worldSettings)
:   m_worldGenType      (worldSettings.generator)
,   m_pWorldSettings    (&worldSettings)
{
    m_heightGen.setSeed     (worldSettings.seed);
    m_biomeNoise.setSeed    (worldSettings.seed);

    m_biomeNoise.setNoiseFunction   (m_worldGenType.getBiomeMapNoise());
}

void Terrain_Generator::reset()
{
    m_maxHeight = 0;
    m_heightMap.reset();
    m_biomeMap.reset();
    m_oakTreeLocations.clear();
    m_littleBlockLoc.clear();
}


void Terrain_Generator::generateBlocksFor(Chunk::Full_Chunk& chunk, World_File& worldFile)
{
    //Only one chunk can generate a time
    m_genMutex.lock();

    m_pChunk = &chunk;
    reset();

    //Check to create a super flat or a terrain world
    if (m_pWorldSettings->isSuperFlat)
    {
        makeSuperFlatWorld();
    }
    else
    {
        makeRegularWorld();
    }

    chunk.hasGeneratedBlockData = true;
    m_genMutex.unlock();
}

/*
    This causes a crash for some odd reason
*/
void Terrain_Generator::makeSuperFlatWorld()
{
    for (int y = 0; y < 13; ++y)
    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int z = 0; z < CHUNK_SIZE; ++z)
    {
        Block::ID block = Block::ID::Grass;
        if (y == 12)
        {
            block = Block::ID::Grass;
        }
        else if (Maths::inRange(y, 9, 12))
        {
            block = Block::ID::Dirt;
        }
        else
        {
            block = Block::ID::Stone;
        }

        m_pChunk->qSetBlock({x, y, z}, block);
    }
}

void Terrain_Generator::makeRegularWorld()
{
    setRandomSeed   ();
    makeBiomeMap    ();

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
        auto id = pos.second;
        Structure::createFromID(id, *m_pChunk, pos.first, m_randomGenerator);
    }
}


Block::ID Terrain_Generator::getBlock(const Block::Position& pos)
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

void Terrain_Generator::setTopBlock(const Block::Position& pos, Block::ID& blockID)
{

    int y = pos.y;
    int biomeKey = m_biomeMap.at(pos.x, pos.z);

    const Biome& biome = m_worldGenType.getBiome(biomeKey);

    if (y >= WATER_LEVEL)   //Above water
    {
        if (y <= BEACH_LEVEL)   //Beach
        {
            blockID = Block::ID::Sand;
        }
        else //Ground blocks
        {
            blockID = (Block::ID)biome.getSurfaceBlock(m_randomGenerator).id;
            if (biome.hasFlora())
            {
                if (m_randomGenerator.intInRange(0, biome.getFloraFrequency()) == 5)
                {
                    auto block =  biome.getFloraBlock(m_randomGenerator);
                    m_littleBlockLoc.emplace_back(std::make_pair(pos, block));
                }
            }
            if (biome.hasStructure())
            {
                if (m_randomGenerator.intInRange(0, biome.getTreeFrequencey()) == 5)
                {
                    auto tree =  biome.getTree(m_randomGenerator);
                    m_oakTreeLocations.emplace_back(std::make_pair(pos, tree));
                }
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


void Terrain_Generator::setRandomSeed()
{
    m_randomGenerator.setSeed(Hasher::hash(static_cast<int>(m_pWorldSettings->seed),
                                           m_pChunk->getPosition().x,
                                           m_pChunk->getPosition().y));
}

/*
    Creates an area of the height map for the chunk currently being generated
    between the specified regions.
    It will create a height at the 4 corners of the area, and then
    bilinear-interpolate between them
*/
void Terrain_Generator::makeHeightSection(int xMin, int zMin, int xMax, int zMax)
{
    auto getHeightAt = [&](int indexA, int indexB)
    {
        m_heightGen.setNoiseFunction(m_worldGenType.getBiome(m_biomeMap.at(indexA, indexB)).getNoise());
        return m_heightGen.getValue(indexA,
                                    indexB,
                                    m_pChunk->getPosition().x,
                                    m_pChunk->getPosition().y);

    };

    int bottomLeft  = getHeightAt(xMin, zMin);
    int bottomRight = getHeightAt(xMax, zMin);
    int topLeft     = getHeightAt(xMin, zMax);
    int topRight    = getHeightAt(xMax, zMax);

    int itr = 0;
    for (int32_t x = xMin ; x < xMax; ++x)
    for (int32_t z = zMin ; z < zMax; ++z)
    {
        itr++;
        int height =
            Maths::bilinearInterpolate(bottomLeft, topLeft, bottomRight, topRight, //The values to interpolate between
                                       xMin, xMax,             //X range of the values
                                       zMin, zMax,             //Z Range of the values
                                       x, z);               //X and Z position to find value for

        m_heightMap.at(x, z) = height;
        m_maxHeight = std::max(m_maxHeight, height);
    }
}

void Terrain_Generator::makeHeightMap()
{
    static constexpr int HCS = CHUNK_SIZE / 2;
    static constexpr int CS  = CHUNK_SIZE;

    ///@TODO For loop?
    makeHeightSection(0,    0,      HCS,    HCS);
    makeHeightSection(HCS,  0,      CS,     HCS);
    makeHeightSection(0,    HCS,    HCS,    CS);
    makeHeightSection(HCS,  HCS,    CS,     CS);

    makeHeightSection(4, 2, 12, 7);
}

void Terrain_Generator::makeBiomeMap()
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


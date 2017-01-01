#include "World_Generator.h"

#include <algorithm>


#include "../../Util/Noise_Generator.h"
#include "../../Util/Hasher.h"
#include "../../Util/Random.h"

#include "../World.h"
#include "../Block/D_Blocks.h"
#include "../Chunk/Chunk.h"

namespace
{
    Biome forestBiome;
    Biome dirtForest;
    Biome desertBiome;
    Biome grasslandBiome;

    Noise::Generator terrainNoise;
    Noise::Generator biomeNoise;
}

World_Generator::World_Generator(Chunk& chunk,
                                 uint32_t seed)
:   m_p_chunk   (&chunk)
,   m_maxHeight (World_Constants::WATER_LEVEL + 1)
,   m_seed      (seed)
{
    terrainNoise.setNoiseFunction({9, 225, 0.5, 260, -30});  //DO NOT TOUCH PLEASE
    biomeNoise.setNoiseFunction({7, 250, 0.5, 240, 0});
    terrainNoise.setSeed(m_seed);
    biomeNoise.setSeed((m_seed * 2) / 25);

    static bool biomesSetUp = false;
    if (!biomesSetUp)
    {
        setUpBiomes();
        biomesSetUp = true;
    }
}

void World_Generator::generate()
{
    generateHeightMap   ();
    generateBiomeMap    ();

    generateBlockData();

    m_heightMap.clear();
    m_biomeMap.clear();

    m_heightMap.shrink_to_fit();
    m_biomeMap.shrink_to_fit();

}

void World_Generator::generateHeightMap()
{
    generateMap(m_heightMap, terrainNoise);

    auto val = *std::max_element(m_heightMap.begin(), m_heightMap.end());
    if (val > m_maxHeight)
    {
        m_maxHeight = val;
    }

}

void World_Generator::generateBiomeMap()
{
    generateMap(m_biomeMap, biomeNoise);
}


void World_Generator::generateMap(std::vector<int>& valueMap, const Noise::Generator& noiseGenerator)
{
    for (int x = 0 ; x < World_Constants::CHUNK_SIZE ; ++x)
    {
        for (int z = 0 ; z < World_Constants::CHUNK_SIZE ; ++z)
        {
            auto value = noiseGenerator.getValue(x,
                                                 z,
                                                 m_p_chunk->getLocation().x,
                                                 m_p_chunk->getLocation().z);
            valueMap.push_back(value);
        }
    }
}


void World_Generator::generateBlockData()
{
    for (int y = 0  ; y < m_maxHeight + 1 ; ++y)
    {
        for (int x = 0 ; x < World_Constants::CHUNK_SIZE ; ++x)
        {
            for (int z = 0 ; z < World_Constants::CHUNK_SIZE ; ++z)
            {
                setRandomSeed(x, y, z);

                auto index = (x * World_Constants::CHUNK_SIZE + z);

                setActiveBiome(m_biomeMap[index]);
                setBlock({x, y, z}, m_heightMap[index]);
            }
        }
    }

    //Generate flora
    for (auto& s : m_flora)
    {
        auto& loc = s.first;
        m_p_chunk->addBlock({loc.x, loc.y + 1, loc.z}, *s.second);
    }
    m_flora.clear();

    //Generate strucutres eg trees
    for (auto& s : m_structures)
    {
        s.second(*m_p_chunk, s.first, false);
    }
    m_structures.clear();
}

void World_Generator::setRandomSeed(int x, int y, int z)
{
    Random::setSeed(Hasher::hash(x + World_Constants::CHUNK_SIZE * m_p_chunk->getLocation().x + m_seed,
                                 y + m_seed * x * z,
                                 z + World_Constants::CHUNK_SIZE * m_p_chunk->getLocation().z + m_seed)); //This for trees, so they gen in the same place
}

//Generates all the blocks in a given chunk.
void World_Generator::setBlock(const Block_Location& location, int h)
{
    auto y = location.y;

    if (y > h)  //Above the ground
    {
        y > World_Constants::WATER_LEVEL ?
            setBlock(location, Block::get(Block::ID::Air))  :
            setBlock(location, Block::get(Block::ID::Water));
    }
    else if (y == h)    //Surface levels
    {
        if (y < World_Constants::SNOW_LEVEL)
        {
            if (y > World_Constants::BEACH_LEVEL) //Surface/ main land area
            {
                setBlock(location, m_p_activeBiome->getBlock());
                if (m_p_activeBiome->hasTrees()) //Trees
                    tryAddTree(location);
                if (m_p_activeBiome->hasFlora()) //Flora eg Rose and tall grass
                    tryAddFlora(location);
            }
            else if (y <= World_Constants::BEACH_LEVEL && y >= World_Constants::WATER_LEVEL) //Beach
            {
                setBlock(location, Block::get(Block::ID::Sand));
            }
            else // Underwater surface
            {
                 (y < 2) ?
                    setBlock(location, Block::get(Block::ID::Bedrock)) :
                    Random::integer(0, 3) < 1 ?
                        setBlock(location, Block::get(Block::ID::Dirt)) :
                        setBlock(location, Block::get(Block::ID::Sand));
            }
        }
        else    //High mountains
        {
            Random::integer(1, 5) < 2 ?
                setBlock(location, Block::get(Block::ID::Snow)) :
                setBlock(location, m_p_activeBiome->getBlock());
        }
    }
    else if (h - y < m_p_activeBiome->getDepth() && y > World_Constants::BEACH_LEVEL) //Slightly underground (biome)
    {
        setBlock(location, m_p_activeBiome->getBlock());
    }
    else if (y < h && y >= h - 4)   //Slighty underground
    {
            y > World_Constants::BEACH_LEVEL ?
                setBlock(location, Block::get(Block::ID::Dirt)) :
                setBlock(location, Block::get(Block::ID::Sand));
    }
    else if (y < 2)
    {
        setBlock(location, Block::get(Block::ID::Bedrock));
    }
    else    //Deep underground
    {
        setBlock(location, Block::get(Block::ID::Stone));
    }
}

void World_Generator::setBlock(const Block_Location& location, const Block::Block_Type& block)
{
    m_p_chunk->addBlock(location, block);
}

void World_Generator::tryAddTree(const Block_Location& location)
{
    if (location.y < World_Constants::SNOW_LEVEL - 15)
    {
        if (Random::integer(1, m_p_activeBiome->getTreeFrequency()) == 1)
        {
            m_structures.insert(std::make_pair(location, m_p_activeBiome->getTreeFunction()));
        }
    }
}

void World_Generator::tryAddFlora(const Block_Location& location)
{
    if (location.y < World_Constants::SNOW_LEVEL - 15)
    {
        if (Random::integer(1, m_p_activeBiome->getFloraFrequency()) == 1)
        {
            //Make sure plants are not placed where a structure is going to be.
            if (m_structures.find(location) == m_structures.end())
                m_flora.insert(std::make_pair(location, &m_p_activeBiome->getFlora()));
        }
    }
}


void World_Generator::setActiveBiome(int value)
{
    if (value > 230)
        m_p_activeBiome = &grasslandBiome;
    else if (value <= 230 && value > 170)
        m_p_activeBiome = &dirtForest;
    else if ( value <= 170 && value > 70)
        m_p_activeBiome = &forestBiome;
    else
        m_p_activeBiome = &desertBiome;
}


void World_Generator::setUpBiomes ()
{
    //===================================
    //Forest
    forestBiome.addBlock(Block::get(Block::ID::Grass), 1);
    forestBiome.setDepth(1);

    forestBiome.addTree(Structure::makeOak);
    forestBiome.setTreeFrequency(45);

    forestBiome.addFlora(Block::get(Block::ID::Tall_Grass), 1);
    forestBiome.addFlora(Block::get(Block::ID::Rose), 1);
    forestBiome.setFloraFrequency(40);

    //===================================
    //Dirt Forest
    dirtForest.addBlock(Block::get(Block::ID::Grass), 5);
    dirtForest.addBlock(Block::get(Block::ID::Dirt),  1);
    dirtForest.setDepth(1);

    dirtForest.addTree(Structure::makeOak);
    dirtForest.setTreeFrequency(250);

    dirtForest.addFlora(Block::get(Block::ID::Tall_Grass), 2);
    dirtForest.addFlora(Block::get(Block::ID::Rose), 1);
    dirtForest.setFloraFrequency(60);

    //===================================
    //Desert
    desertBiome.addBlock(Block::get(Block::ID::Sand), 1);
    desertBiome.setDepth(3);

    desertBiome.addTree(Structure::makeCactus);
    desertBiome.setTreeFrequency(1200);

    desertBiome.addFlora(Block::get(Block::ID::Dead_Shrub), 1);
    desertBiome.setFloraFrequency(400);

    //===================================
    //Grassland
    grasslandBiome.addBlock(Block::get(Block::ID::Grass), 1);

    grasslandBiome.setDepth(1);

    grasslandBiome.addTree(Structure::makeOak);
    grasslandBiome.setTreeFrequency(1000);

    grasslandBiome.addFlora(Block::get(Block::ID::Tall_Grass), 3);
    grasslandBiome.addFlora(Block::get(Block::ID::Rose), 1);
    grasslandBiome.setFloraFrequency(20);
}

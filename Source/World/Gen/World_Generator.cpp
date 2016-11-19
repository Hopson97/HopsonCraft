#include "World_Generator.h"

#include <algorithm>

#include "../Chunk/Chunk.h"
#include "../Block/D_Blocks.h"

#include "../../Util/Noise_Generator.h"
#include "../../Util/Hasher.h"
#include "../../Util/Random.h"

namespace
{
    Biome forestBiome;
    Biome dirtForest;
    Biome desertBiome;
    Biome grasslandBiome;

    Noise::Generator terrainNoise;
    Noise::Generator biomeNoise;
}

World_Generator::World_Generator(Chunk& chunk)
:   m_p_chunk   (&chunk)
,   m_maxHeight (Chunk::WATER_LEVEL + 1)
{
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
    for (int x = 0 ; x < Chunk::SIZE ; x++)
    {
        for (int z = 0 ; z < Chunk::SIZE ; z++)
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
    for (int y = 0  ; y < m_maxHeight + 1 ; y++)
    {
        for (int x = 0 ; x < Chunk::SIZE ; x++)
        {
            for (int z = 0 ; z < Chunk::SIZE ; z++)
            {
                setRandomSeed(x, y, z);

                auto index = (x * Chunk::SIZE + z);
                auto height = m_heightMap.at(index);
                setActiveBiome(m_biomeMap.at(index));

                setBlock({x, y, z}, height);
            }
        }
    }

    //Generate strucutres eg trees
    for (auto& s : m_structures)
    {
        s.second(*m_p_chunk, s.first);
    }
    m_structures.clear();

    //Generate flowers and tall grass
    for (auto& s : m_flora)
    {
        auto& loc = s.first;
        m_p_chunk->getBlocks().setBlock({loc.x, loc.y + 1, loc.z}, *s.second);
    }
    m_structures.clear();
}

void World_Generator::setRandomSeed(int x, int y, int z)
{
    auto seed = Noise::getSeed();

    Random::setSeed(Hasher::hash(x + Chunk::SIZE * m_p_chunk->getLocation().x + seed,
                                 y + seed,
                                 z + Chunk::SIZE * m_p_chunk->getLocation().z + seed)); //This for trees, so they gen in the same place
}

void World_Generator::setBlock(const Block_Location& location, int h)
{
    auto y = location.y;

    if (y > h)  //Above the ground
    {
        y > Chunk::WATER_LEVEL ?
            setBlock(location, Block::air)  :
            setBlock(location, Block::water);
    }
    else if (y == h)    //Surface levels
    {
        if (y < Chunk::SNOW_LEVEL)
        {
            if (y > Chunk::BEACH_LEVEL) //Surface/ main land area
            {
                setBlock(location, m_p_activeBiome->getBlock());
                if (m_p_activeBiome->hasTrees()) //Trees
                    tryAddTree(location);
                if (m_p_activeBiome->hasFlora()) //Flora eg Rose and tall grass
                    tryAddFlora(location);
            }
            else if (y <= Chunk::BEACH_LEVEL && y >= Chunk::WATER_LEVEL) //Beach
            {
                setBlock(location, Block::sand);
            }
            else // Underwater surface
            {
                Random::integer(0, 3) < 1 ?
                    setBlock(location, Block::dirt) :
                    setBlock(location, Block::sand);
            }
        }
        else    //High mountains
        {
            Random::integer(1, 5) < 2 ?
                setBlock(location, Block::snow) :
                setBlock(location, m_p_activeBiome->getBlock());
        }
    }
    else if (h - y < m_p_activeBiome->getDepth() && y > Chunk::BEACH_LEVEL) //Slightly underground (biome)
    {
        setBlock(location, m_p_activeBiome->getBlock());
    }
    else if (y < h && y >= h - 4)   //Slighty underground
    {
            y > Chunk::BEACH_LEVEL ?
                setBlock(location, Block::dirt) :
                setBlock(location, Block::sand);
    }
    else    //Deep underground
    {
        setBlock(location, Block::stone);
    }
}

void World_Generator::setBlock(const Block_Location& location, const Block_t& block)
{
    m_p_chunk->getBlocks().qSetBlock(location, block);
}

void World_Generator::tryAddTree(const Block_Location& location)
{
    if (location.y < Chunk::SNOW_LEVEL - 15)
    {
        if (Random::integer(1, m_p_activeBiome->getTreeFrequency()) == 1)
        {
            m_structures.insert(std::make_pair(location, m_p_activeBiome->getTreeFunction()));
        }
    }
}

void World_Generator::tryAddFlora(const Block_Location& location)
{
    if (location.y < Chunk::SNOW_LEVEL - 15)
    {
        if (Random::integer(1, m_p_activeBiome->getFloraFrequency()) == 1)
        {
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
    terrainNoise.setNoiseFunction({10, 225, 0.5, 260, -35});  //DO NOT TOUCH PLEASE
    biomeNoise.setNoiseFunction({7, 250, 0.5, 240, 0});

    terrainNoise.setSeed(Noise::getSeed());
    biomeNoise.setSeed((Noise::getSeed() * 12) / 33);

    //===================================
    //Forest
    forestBiome.addBlock(Block::grass, 1);
    forestBiome.setDepth(1);

    forestBiome.addTree(Structure::makeOak);
    forestBiome.setTreeFrequency(45);

    forestBiome.addFlora(Block::tallGrass, 1);
    forestBiome.addFlora(Block::rose, 1);
    forestBiome.setFloraFrequency(40);

    //===================================
    //Dirt Forest
    dirtForest.addBlock(Block::grass, 40);
    dirtForest.addBlock(Block::dirt, 1);

    dirtForest.setDepth(1);

    dirtForest.addTree(Structure::makeOak);
    dirtForest.setTreeFrequency(150);

    dirtForest.addFlora(Block::tallGrass, 2);
    dirtForest.addFlora(Block::rose, 1);
    dirtForest.setFloraFrequency(60);

    //===================================
    //Desert
    desertBiome.addBlock(Block::sand, 100);
    desertBiome.setDepth(3);

    desertBiome.addTree(Structure::makeCactus);
    desertBiome.setTreeFrequency(1200);

    desertBiome.addFlora(Block::deadShrub, 1);
    desertBiome.setFloraFrequency(400);

    //===================================
    //Grassland
    grasslandBiome.addBlock(Block::grass, 80);
    grasslandBiome.addBlock(Block::dirt, 1);

    grasslandBiome.setDepth(1);

    grasslandBiome.addTree(Structure::makeOak);
    grasslandBiome.setTreeFrequency(750);

    grasslandBiome.addFlora(Block::tallGrass, 3);
    grasslandBiome.addFlora(Block::rose, 1);
    grasslandBiome.setFloraFrequency(40);
}

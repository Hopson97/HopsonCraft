#include "World_Generator.h"

#include <algorithm>

#include "../Chunk/Chunk.h"
#include "../Block/D_Blocks.h"

#include "../../Util/Noise_Generator.h"
#include "../../Util/Hasher.h"
#include "../../Util/Random.h"

namespace
{
    Biome m_forestBiome;
    Biome m_dirtForest;
    Biome m_desertBiome;
    Biome m_grasslandBiome;

    Noise::Generator m_terrainNoise;
    Noise::Generator m_biomeNoise;
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
    generateMap(m_heightMap, m_terrainNoise);

    auto val = *std::max_element(m_heightMap.begin(), m_heightMap.end());
    if (val > m_maxHeight)
    {
        m_maxHeight = val;
    }

}

void World_Generator::generateBiomeMap()
{
    generateMap(m_biomeMap, m_biomeNoise);
}


void World_Generator::generateMap(std::vector<int>& valueMap, const Noise::Generator& noiseGenerator)
{
    for (int x = 0 ; x < Chunk::SIZE ; x++)
    {
        for (int z = 0 ; z < Chunk::SIZE ; z++)
        {
            auto value = noiseGenerator.getHeight (x,
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
        for (char x = 0 ; x < Chunk::SIZE ; x++)
        {
            for (char z = 0 ; z < Chunk::SIZE ; z++)
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

void World_Generator::setRandomSeed(char x, int y, char z)
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
                tryAddTree(location);
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
        m_p_activeBiome = &m_grasslandBiome;
    else if (value <= 230 && value > 170)
        m_p_activeBiome = &m_dirtForest;
    else if ( value <= 170 && value > 65)
        m_p_activeBiome = &m_forestBiome;
    else
        m_p_activeBiome = &m_desertBiome;
}


void World_Generator::setUpBiomes ()
{
    m_terrainNoise.setNoiseFunction({10, 225, 0.5, 260, -25});  //DO NOT TOUCH PLEASE
    m_biomeNoise.setNoiseFunction({7, 250, 0.5, 240, 0});

    m_terrainNoise.setSeed(Noise::getSeed());
    m_biomeNoise.setSeed((Noise::getSeed() * 12) / 33);

    //===================================
    //Forest
    m_forestBiome.addBlock(Block::grass, 1);
    m_forestBiome.setDepth(1);

    m_forestBiome.addTree(Structure::makeOak);
    m_forestBiome.setTreeFrequency(45);

    m_forestBiome.addFlora(Block::tallGrass, 1);
    m_forestBiome.addFlora(Block::rose, 1);
    m_forestBiome.setFloraFrequency(40);

    //===================================
    //Dirt Forest
    m_dirtForest.addBlock(Block::grass, 4);
    m_dirtForest.addBlock(Block::dirt, 1);

    m_dirtForest.setDepth(1);

    m_dirtForest.addTree(Structure::makeOak);
    m_dirtForest.setTreeFrequency(150);

    m_dirtForest.addFlora(Block::tallGrass, 2);
    m_dirtForest.addFlora(Block::rose, 1);
    m_dirtForest.setFloraFrequency(60);

    //===================================
    //Desert
    m_desertBiome.addBlock(Block::sand, 1);
    m_desertBiome.setDepth(3);

    m_desertBiome.addTree(Structure::makeCactus);
    m_desertBiome.setTreeFrequency(300);

    m_desertBiome.addFlora(Block::deadShrub, 1);
    m_desertBiome.setFloraFrequency(280);

    //===================================
    //Grassland
    m_grasslandBiome.addBlock(Block::grass, 1);

    m_grasslandBiome.setDepth(3);

    m_grasslandBiome.addTree(Structure::makeOak);
    m_grasslandBiome.setTreeFrequency(750);

    m_grasslandBiome.addFlora(Block::tallGrass, 3);
    m_grasslandBiome.addFlora(Block::rose, 1);
    m_grasslandBiome.setFloraFrequency(40);
}

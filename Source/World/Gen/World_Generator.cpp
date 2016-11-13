#include "World_Generator.h"

#include <algorithm>

#include "../Chunk/Chunk.h"
#include "../Block/D_Blocks.h"

#include "../../Util/Noise_Generator.h"
#include "../../Util/Hasher.h"
#include "../../Util/Random.h"

World_Generator::World_Generator(Chunk& chunk)
:   m_p_chunk   (&chunk)
,   m_maxHeight (Chunk::WATER_LEVEL + 1)
{
    m_terrainNoise.setNoiseFunction({10, 230, 0.5, 250, -25});
    m_biomeNoise.setNoiseFunction({8, 250, 0.6, 325, 0});

    m_terrainNoise.setSeed(Noise::getSeed());
    m_biomeNoise.setSeed(Noise::getSeed() << 1);
    setUpBiomes();
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
    else if (h - y <= m_p_activeBiome->getDepth() && y > Chunk::BEACH_LEVEL) //Slightly underground (biomes)
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
    if (location.y < 218)
    if (Random::integer(1, 100) == 1)
    {
        //m_structureLocations.emplace_back(*m_p_chunk, location, &Structure::createOak);
    }
}

void World_Generator::setActiveBiome(int value)
{
    if (value > 240)
        m_p_activeBiome = &m_snowBiome;
    else if ( value <= 240 && value > 110)
        m_p_activeBiome = &m_forestBiome;
    else if ( value <= 110 /*&& value > 0*/)
        m_p_activeBiome = &m_desertBiome;
}


void World_Generator::setUpBiomes ()
{
    //forest
    m_forestBiome.addBlock(Block::grass, 1);
    m_forestBiome.setDepth(1);

    //desert
    m_desertBiome.addBlock(Block::sand, 1);
    m_desertBiome.setDepth(3);

    //snow
    m_snowBiome.addBlock(Block::snow, 1);
    m_snowBiome.setDepth(3);

}

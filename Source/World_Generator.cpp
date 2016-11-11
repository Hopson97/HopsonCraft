#include "World_Generator.h"

#include "Chunk.h"
#include "D_Blocks.h"
#include "Noise_Generator.h"

#include "Hasher.h"
#include "Random.h"

World_Generator::World_Generator(Chunk& chunk)
:   m_p_chunk   (&chunk)
,   m_maxHeight (Chunk::WATER_LEVEL + 1)
{ }

void World_Generator::generate()
{
    generateHeightMap   ();
    generateBiomeMap    ();

    generateMap();

    m_heightMap.clear();
    m_biomeMap.clear();
}

void World_Generator::generateHeightMap()
{
    static Noise_Generator::Data terrainNoise (8, 200, 0.55, 320);
    Noise_Generator::setNoiseFunction(terrainNoise);

    for (int x = 0 ; x < Chunk::SIZE ; x++)
    for (int z = 0 ; z < Chunk::SIZE ; z++)
    {
        auto height =  Noise_Generator::getHeight (x,
                                                   z,
                                                   m_p_chunk->getLocation().x,
                                                   m_p_chunk->getLocation().z);
        if (height > m_maxHeight)
            m_maxHeight = height;

        m_heightMap.push_back(height);
    }
}

void World_Generator::generateBiomeMap()
{
    static Noise_Generator::Data biomeNoise (10, 265, 0.61, 600);
    Noise_Generator::setNoiseFunction(biomeNoise);

    for (int x = 0 ; x < Chunk::SIZE ; x++)
    for (int z = 0 ; z < Chunk::SIZE ; z++)
    {
        auto value = Noise_Generator::getHeight (x,
                                                 z,
                                                 m_p_chunk->getLocation().x,
                                                 m_p_chunk->getLocation().z);
        m_biomeMap.push_back(value);
    }
}

void World_Generator::generateMap()
{
    for (int y = 0  ; y < m_maxHeight + 1 ; y++)
    for (char x = 0 ; x < Chunk::SIZE ; x++)   //I hate seeing the pyrmid of death, so umma just do this
    for (char z = 0 ; z < Chunk::SIZE ; z++)
    {
        setRandomSeed(x, y, z);
        auto h = m_heightMap.at(x * Chunk::SIZE + z);
        setBlock({x, y, z}, h);
    }


}

void World_Generator::setRandomSeed(char x, int y, char z)
{
    auto seed = Noise_Generator::getSeed();

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
                setBlock(location, Block::grass);
            }
            else if (y <= Chunk::BEACH_LEVEL && y >= Chunk::WATER_LEVEL) //Beach
            {
                setBlock(location, Block::sand);
            }
            else // Underwater surface
            {
                Random::integer(0, 3) < 1 ?
                    setBlock(location, Block::sand) :
                    setBlock(location, Block::dirt);
            }
        }
        else    //High mountains
        {
            Random::integer(1, 5) < 2 ?
                setBlock(location, Block::snow) :
                setBlock(location, Block::grass);
        }
    }
    else if (y < h && y >= h - 4)   //Slighty underground
    {
        setBlock(location, Block::dirt);
    }
    else
    {
        setBlock(location, Block::stone);
    }
}

void World_Generator::setBlock(const Block_Location& location, const Block_t& block)
{
    m_p_chunk->getBlocks().qSetBlock(location, block);
}


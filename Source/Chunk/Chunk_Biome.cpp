#include "Chunk.h"

#include "D_Blocks.h"
#include "Random.h"
#include "Hasher.h"
#include "Noise_Generator.h"

namespace
{
    struct Biome
    {
        Biome(Block::Block_Base& surface, int depth, int treeChance, std::vector<Block_Location>& treeLocations, bool isHot)
        :   surfaceBlock    (&surface)
        ,   depth           (depth)
        ,   treeChance      (treeChance)
        ,   treeLocations   (&treeLocations)
        ,   isHot           (isHot)
        {}

        Block::Block_Base* surfaceBlock;
        int depth;
        int treeChance;
        std::vector<Block_Location>* treeLocations;
        bool isHot;
    };

    const Biome& getBiome (int biomeValue, Biome& forest, Biome& fields, Biome& desert, Biome& snow)
    {
        if (biomeValue > 270) return snow;
        else if (biomeValue <= 270 && biomeValue > 180 ) return fields;
        else if (biomeValue <= 180 && biomeValue >= 135) return forest;
        else return desert;
    }
}

void Chunk::generateChunk(int maxHeight, const std::vector<int>& heightMap, const std::vector<int>& biomeMap)
{
    static const auto noiseSeed = Noise_Generator::getSeed();

    Biome forest(Block::grass, 1, 70, m_treeLocations, false);
    Biome desert(Block::sand, 5, 1000, m_cactusLocations, true);
    Biome fields(Block::grass, 1, 1000, m_treeLocations, false);
    Biome snow  (Block::snow, 3, 1000, m_treeLocations, false);

    for (int y = 0; y < maxHeight + 1 ; y++)
    {
        for (int x = 0 ; x < SIZE ; x++)
        {
            for (int z = 0 ; z < SIZE ; z++)
            {
                Random::setSeed(Hasher::hash(x + noiseSeed,
                                             y + noiseSeed,
                                             z + noiseSeed)); //This for trees, so they gen in the same place


                auto* biome = &getBiome(biomeMap.at(x * SIZE + z), forest, fields, desert, snow);

                int h = heightMap.at (x * SIZE + z);
                if (y > h)
                {
                    y <= WATER_LEVEL ?
                        qSetBlock({x, y, z}, Block::water) :
                        qSetBlock({x, y, z}, Block::air);
                }
                else if (y <= h && y >= h - biome->depth)
                {
                    if (y > BEACH_LEVEL) //Top levels
                    {
                        if ( y <= SNOW_LEVEL || biome->isHot )
                        {
                            qSetBlock({x, y, z}, *biome->surfaceBlock );

                            if ( Random::integer(0, biome->treeChance) == 1  &&
                               (x > 3 && x < SIZE - 3) &&
                               (z > 3 && z < SIZE - 3)
                                && y <= SNOW_LEVEL - 10)
                            {
                                biome->treeLocations->emplace_back(x, y, z);    //Trees
                            }
                        }
                        else
                        {
                            Random::integer(y, maxHeight + 10) < y + 5?
                                qSetBlock({x, y, z}, Block::snow) :
                                qSetBlock({x, y, z}, *biome->surfaceBlock );
                        }

                    }
                    else if (y <= BEACH_LEVEL && y >= WATER_LEVEL) //Beach
                    {
                        qSetBlock({x, y, z}, Block::sand);
                    }
                    else
                    {
                        Random::integer(0, 10) < 6 ?
                            qSetBlock({x, y, z}, Block::sand)   :
                            qSetBlock({x, y, z}, Block::dirt);
                    }
                }
                else  if (y < h && y > h - 5)
                {
                    qSetBlock({x, y, z}, Block::dirt);
                }
                else
                {
                    qSetBlock({x, y, z}, Block::stone);
                }
            }
        }
    }
}

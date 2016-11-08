#include "Chunk.h"

#include "D_Blocks.h"
#include "Random.h"
namespace
{
    struct Biome
    {
        Biome(Block::Block_Base& surface, int depth, bool hasTrees)
        :   surfaceBlock    (&surface)
        ,   depth           (depth)
        ,   hasTrees        (hasTrees)
        {}

        Block::Block_Base* surfaceBlock;
        int depth;
        bool hasTrees;
    };

    Biome forest(Block::grass, 1, true);
    Biome desert(Block::sand, 5, false);

    const Biome& getBiome (int biomeValue)
    {
        if (biomeValue > 100 ) return forest;
        else return desert;
    }
}

void Chunk::generateChunk(int maxHeight, const std::vector<int>& heightMap, const std::vector<int>& biomeMap)
{
    if(maxHeight <= WATER_LEVEL) maxHeight = WATER_LEVEL + 1;

    for (int y = 0; y < maxHeight + 1 ; y++)
    {
        for (int x = 0 ; x < SIZE ; x++)
        {
            for (int z = 0 ; z < SIZE ; z++)
            {
                const Biome* biome = &getBiome(biomeMap.at(x * SIZE + z));

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
                        if ( y <= SNOW_LEVEL )
                        {
                            qSetBlock({x, y, z}, *biome->surfaceBlock );
                            if (biome->hasTrees)
                            {
                                if ( Random::integer(0, y) == 1  &&
                                   (x > 3 && x < SIZE - 3) &&
                                   (z > 3 && z < SIZE - 3)
                                    && y <= SNOW_LEVEL - 10)
                                {
                                    m_treeLocations.emplace_back(x, y, z);    //Trees
                                }
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

#include "Chunk.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Block/Block.h"
#include "Texture/Texture_Atlas.h"
#include "Loader.h"
#include "Random.h"
#include "Block/D_Blocks.h"
#include "Chunk_Map.h"
#include "Debug_Display.h"
#include "Noise_Generator.h"
#include "Tree.h"

namespace
{
    Noise_Generator::Data terrainNoise  (8, 240, 0.49, 220);
    Noise_Generator::Data biomeNoise    (10, 255, 0.61, 500);
}

void Chunk::generateBlockData()
{
    //Create height map
    auto maxHeight = WATER_LEVEL + 1;
    std::vector<int> heightMap;
    Noise_Generator::setNoiseFunction(terrainNoise);
    for (int x = 0; x < SIZE ; x ++)
    {
        for (int z = 0 ; z < SIZE ; z++)
        {
            auto height =  Noise_Generator::getHeight (x,
                                                        z,
                                                        m_location.x,
                                                        m_location.z );
            if (height > maxHeight) maxHeight = height;
            heightMap.push_back(height);
        }
    }

    //Create biome map
    std::vector<int> biomeMap;
    Noise_Generator::setNoiseFunction(biomeNoise);
    for (int x = 0; x < SIZE ; x ++)
    {
        for (int z = 0 ; z < SIZE ; z++)
        {
            auto value =  Noise_Generator::getHeight(x,
                                                     z,
                                                     m_location.x,
                                                     m_location.z );
            biomeMap.push_back(value);
        }
    }

    this->generateChunk(maxHeight, heightMap, biomeMap);
}

void Chunk::generateStructureData ()
{
/*
    for (auto& location : m_treeLocations)
    {
        Tree::makeOakTree(*this, location);
    }
    m_treeLocations.clear();

    for(auto& location : m_cactusLocations)
    {
        Tree::makeCactus(*this, location);
    }
    m_cactusLocations.clear();
*/
}

void Chunk::loadBlockData ()
{
    std::ifstream inFile(getFileString());

    if(!inFile.is_open())
        return;

    int x, y, z, id;

    while(inFile.peek() != EOF)
    {
        inFile >> x >> y >> z >> id;
        m_blocks.m_addedBlocks[{x, y, z}] = id;
    }

    for (auto& block : m_blocks.m_addedBlocks)
    {
        int idNum = block.second;
        Block::ID id = static_cast<Block::ID>(idNum);

        m_blocks.qSetBlock(block.first, Block::getBlockFromId(id));
    }
}

void Chunk::generateMesh ()
{
    m_p_chunkMap->addChunk({m_location.x + 1, m_location.z});
    m_p_chunkMap->addChunk({m_location.x, m_location.z + 1});
    m_p_chunkMap->addChunk({m_location.x - 1, m_location.z});
    m_p_chunkMap->addChunk({m_location.x, m_location.z - 1});

    m_mesh.generateMesh(m_blocks.getLayerCount());

    m_hasMesh       = true;
    m_hasBuffered   = false;
}

void Chunk::bufferMesh ()
{
    m_mesh.bufferMesh();

    m_hasBuffered = true;
}


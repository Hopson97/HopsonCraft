#include "Chunk.h"

#include <fstream>
#include <iostream>

#include "../Block/D_Blocks.h"
#include "../Block/Block_Type/Block_Type.h"

#include "../../Maths/Matrix_Maths.h"

#include "../../Input/Function_Toggle_Key.h"
#include "../../Util/Noise_Generator.h"

#include "Chunk_Map.h"

#include "../World_Constants.h"

Chunk::Chunk(const Chunk_Location& position,
              Chunk_Map& chunkMap,
              const Texture_Atlas& blockAtlas,
              unsigned seed,
              const std::string& worldName)
:   Entity          ({0, 0, 0}, {position.x * World::CHUNK_SIZE, 0,
                                 position.z * World::CHUNK_SIZE})
,   m_location      (position)
,   m_p_chunkMap    (&chunkMap)
,   m_p_atlas       (&blockAtlas)
,   m_mesh          (*this)
,   m_blocks        (*this, m_location, *m_p_chunkMap)
,   m_worldGenerator(*this, seed)
,   m_modelMatrix   (Maths::createModelMatrix(*this))
{
    m_worldGenerator.generate();
    loadBlockData (worldName);

    m_hasBlockData = true;
}

void Chunk::addBlock( const Block_Location& location,
                      const Block::Block_Type& block,
                      bool overrideBlocks)
{
    //Loot loot = getBlocks().getBlock(location).getLoot();

    if(m_updatableBlocks.find(location) != m_updatableBlocks.end())
    {
        m_updatableBlocks[location]->breakBlock();
    }

    if (block.getData().isUpdatable())
    {
        m_updatableBlocks.insert(std::make_pair(location, std::move(block.getUpdatableBlock())));
        m_updatableBlocks.at(location)->setChunk(*this);
    }

    m_blocks.setBlock(location, block, overrideBlocks);
}

bool Chunk::update()
{
    bool hasChanged = false;

    for (auto itr = m_updatableBlocks.begin() ; itr != m_updatableBlocks.end() ;)
    {
        auto& block = itr->second;

        hasChanged = block->update(itr->first);

        if(block->isDestroyed())
        {
            itr = m_updatableBlocks.erase(itr);
        }
        else
        {
            itr++;
        }
    }

    return hasChanged;
}

bool Chunk::hasBlockData () const
{
    return m_hasBlockData;
}

bool Chunk::hasMesh () const
{
    return m_hasMesh;
}

bool Chunk::hasBuffered () const
{
    return m_hasBuffered;
}

void Chunk::generateMesh ()
{
    //sf::Clock c;

    //This is so the chunk mesh generator can know about the blocks in neighbouring chunks
    //This is so that the blocks don't have missing faces, or random underground faces etc
    //The chunk will only be added if there already is not a chunk there.
    m_p_chunkMap->addChunk({m_location.x + 1,   m_location.z        });
    m_p_chunkMap->addChunk({m_location.x,       m_location.z + 1    });
    m_p_chunkMap->addChunk({m_location.x - 1,   m_location.z        });
    m_p_chunkMap->addChunk({m_location.x,       m_location.z - 1    });

    m_mesh.generateMesh(m_blocks.getLayerCount());

    m_hasMesh       = true;
    m_hasBuffered   = false;
    //std::cout << c.getElapsedTime().asSeconds() << std::endl;
}

void Chunk::bufferMesh ()
{
    m_mesh.bufferMesh();
    m_hasBuffered = true;
}

const Texture_Atlas& Chunk::getAtlas() const
{
    return *m_p_atlas;
}


const Chunk_Location& Chunk::getLocation () const
{
    return m_location;
}

const Vector2 Chunk::getPosition () const
{
    return {position.x, position.z};
}

const Chunk_Mesh& Chunk::getMesh() const
{
    return m_mesh;
}


void Chunk::giveDeleteFlag (const std::string& worldName)
{
    saveToFile(worldName);
    m_hasDeleteFlag = true;
}

bool Chunk::hasDeleteFlag () const
{
    return m_hasDeleteFlag;
}

void Chunk::regenMesh()
{
    generateMesh();
    bufferMesh();
    m_hasregenMeshFlag = false;
}

void Chunk::giveRegenMeshFlag()
{
    m_hasregenMeshFlag = true;
}

bool Chunk::hasRegenMeshFlag() const
{
    return m_hasregenMeshFlag;
}

const Matrix4& Chunk::getModelMatrix() const
{
    return m_modelMatrix;
}


std::string Chunk::getFileString(const std::string& worldName)
{
    return "Worlds/" +
            worldName +
            "/" +
            std::to_string(m_location.x)
            + " "
            + std::to_string(m_location.z);
}

const Chunk_Blocks& Chunk::getBlocks() const
{
    return m_blocks;
}


void Chunk::saveToFile(const std::string& worldName)
{
    if(!m_blocks.getAddedBlocks().empty())
    {
        std::ofstream outFile (getFileString(worldName) + ".chunk");

        for(auto& block : m_blocks.getAddedBlocks())
        {
            const Block_Location& l = block.first;

            outFile << l.x << " " << l.y << " " << l.z << " ";  //Block location
            outFile << block.second << std::endl;               //Block ID
        }
    }
}

void Chunk::loadBlockData (const std::string& worldName)
{
    std::ifstream inFile(getFileString(worldName) + ".chunk");

    if(!inFile.is_open())
        return;

    int x,
        z,
        y,
        id;

    while(inFile.peek() != EOF)
    {
        inFile >> x >> y >> z >> id;
        addBlock({x, y, z}, Block::get(id));
    }

    for (auto& block : m_blocks.getAddedBlocks())
    {
        int idNum = block.second;
        Block::ID id = static_cast<Block::ID>(idNum);


        m_blocks.qSetBlock(block.first, Block::get(id));
    }

    //upda

}


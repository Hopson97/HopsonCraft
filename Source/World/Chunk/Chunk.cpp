#include "Chunk.h"

#include <fstream>
#include <iostream>

#include "../Block/D_Blocks.h"
#include "../Block/Block_Type/Block_Type.h"

#include "../../Maths/Matrix_Maths.h"

#include "../../Input/Function_Toggle_Key.h"
#include "../../Util/Noise_Generator.h"

#include "Chunk_Map.h"

#include "../World.h"

Chunk::Chunk(const Chunk_Location& position,
              Chunk_Map& chunkMap,
              const Texture_Atlas& blockAtlas,
              unsigned seed,
              const std::string& worldName)
:   Entity          ({0, 0, 0}, {position.x * World_Constants::CHUNK_SIZE, 0,
                                 position.z * World_Constants::CHUNK_SIZE})
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
    m_blocks.calculateMaxHeights();

    m_hasBlockData = true;
}

void Chunk::addBlock( const Block_Location& location,
                      const Block::Block_Type& block,
                      bool overrideBlocks)
{
    if(m_updatableBlocks.find(location) != m_updatableBlocks.end())
    {
        m_updatableBlocks[location]->breakBlock();
    }

    //We have to request the block data if it is updatable, and then we get the actual updatable block instance from the
    //block type
    if (block.getData().isUpdatable())
    {
        m_updatableBlocks.insert(std::make_pair(location, std::move(block.getUpdatableBlock())));
        m_updatableBlocks[location]->setChunk(*this);
    }

    m_blocks.setBlock(location, (uint8_t)block.getData().getID(), overrideBlocks);

    checkAddedBlockLocation(location);
}

void Chunk::breakBlock(const Block_Location& location,
                       World& world,
                       const Vector3& worldPosition,
                       Block::Break_Type breakType)
{
    auto& block = m_blocks.getBlock(location);
    m_blocks.setBlock(location, (uint8_t)Block::ID::Air, true);
    block.breakBlock(world, *this, worldPosition, breakType);

    //Loot loot = getBlocks().getBlock(location).getLoot();

    checkAddedBlockLocation(location);
}

void Chunk::checkAddedBlockLocation(const Block_Location& location)
{
    if(m_hasBlockData)
    {
        m_blocks.recalculateMaxHeight(location.x, location.z);
    }
    if (m_updatableBlocks.find(location) != m_updatableBlocks.end())
    {
        m_updatableBlocks.erase(location);
    }
}



bool Chunk::tick()
{
    bool chunkHasChanged = false;

    //Regular blocks can tick
    for (int i = 0 ; i < 5 ; i++)
    {
        auto location = Block_Location::getRandom(m_blocks.getLayerCount());

        chunkHasChanged = m_blocks.getBlock(location).tick(location, this) | chunkHasChanged;
    }
    return chunkHasChanged;
}

bool Chunk::update()
{
    bool chunkHasChanged = false;

    //Some blocks, eg furnaces and saplings, have state and update over time
    for (auto itr = m_updatableBlocks.begin() ; itr != m_updatableBlocks.end() ;)
    {
        auto& block = itr->second;

        chunkHasChanged= block->update(itr->first) | chunkHasChanged;

        if(block->isDestroyed())
        {
            itr = m_updatableBlocks.erase(itr);
        }
        else
        {
            itr++;
        }
    }
    return chunkHasChanged;
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
   // std::cout << c.getElapsedTime().asSeconds() << std::endl;
}

//Gives all the vertex data to opengl
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


std::string Chunk::getFileString(const std::string& worldName) const
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

//This function is mostly for the sake of generating chunk meshes
const Chunk_Blocks* Chunk::getAdjBlocks(int yd, int xd) const
{
    Chunk* chunk = m_p_chunkMap->getChunkAt({m_location.x + yd, m_location.z + xd});
    if (chunk)
    {
        return &chunk->getBlocks();
    }
    return nullptr;
}



void Chunk::saveToFile(const std::string& worldName) const
{
    if(!m_blocks.getAddedBlocks().empty())
    {
        std::ofstream outFile (getFileString(worldName) + ".chunk");

        for(auto& block : m_blocks.getAddedBlocks())
        {
            const Block_Location& l = block.first;

            outFile << l.x << " " << l.y << " " << l.z << " ";  //Block location
            outFile << (uint32_t)block.second << std::endl;     //Block ID
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
        y;

    int id;

    while(inFile.peek() != EOF)
    {
        inFile >> x >> y >> z >> id;
        addBlock({x, y, z}, Block::get(id));
    }

    for (auto& block : m_blocks.getAddedBlocks())
    {
        m_blocks.qSetBlock(block.first, (uint8_t)block.second);
    }
}


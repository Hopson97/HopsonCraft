#include "Chunk.h"

#include <fstream>
#include <iostream>
#include <thread>

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

    m_hasGenBaseBlockData = true;

    loadBlockData (worldName);
    m_blocks.calculateMaxHeights();
    m_blocks.calculateChunkLight();

    m_hasBlockData = true;
}

void Chunk::addBlock( const Block_Location& location,
                      const Block::Block_Type& block,
                      bool overrideBlocks)
{
    if (m_updatableBlocks.find(location) != m_updatableBlocks.end())
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

    if(m_hasBlockData)
    {
        m_blocks.recalculateMaxHeight(location.x, location.z);
    }

    if (m_hasGenBaseBlockData)
    {
        m_addedBlocks[location] = &block;
    }
}

void Chunk::breakBlock(const Block_Location& location,
                       World& world,
                       const Vector3& worldPosition,
                       Block::Break_Type breakType)
{

    if (m_updatableBlocks.find(location) != m_updatableBlocks.end())
    {
        m_updatableBlocks[location]->breakBlock();
    }

    auto& block = m_blocks.getBlock(location);
    m_blocks.setBlock(location, (uint8_t)Block::ID::Air, true);
    block.breakBlock(world, *this, worldPosition, breakType);

    if(m_hasBlockData)
    {
        m_blocks.recalculateMaxHeight(location.x, location.z);
    }

    if (m_hasGenBaseBlockData)
    {
        m_addedBlocks[location] = &Block::get(Block::ID::Air);
    }

    //Loot loot = getBlocks().getBlock(location).getLoot();
}

bool Chunk::tick()
{
    bool chunkHasChanged = false;

    int tries = 0;

    //Regular blocks can tick
    auto location = Block_Location::getRandom(m_blocks.getLayerCount());
    while (m_blocks.getBlock(location).getData().getID() == Block::ID::Air)
    {
        location = Block_Location::getRandom(m_blocks.getLayerCount());
        tries++;
        if (tries >= 25)
            return false;
    }

    chunkHasChanged = m_blocks.getBlock(location).tick(location, *this) | chunkHasChanged;

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
    //This also helps for the sake of lighting calculations
    m_p_chunkMap->addChunk({m_location.x + 1,   m_location.z        });
    m_p_chunkMap->addChunk({m_location.x,       m_location.z + 1    });
    m_p_chunkMap->addChunk({m_location.x - 1,   m_location.z        });
    m_p_chunkMap->addChunk({m_location.x,       m_location.z - 1    });

    m_blocks.calculateChunkLight();
    m_blocks.calculateChunkEdgeLight();

    m_mesh.generateMesh(m_blocks.getLayerCount());

    m_hasMesh       = true;
    m_hasBuffered   = false;
    //std::cout << c.getElapsedTime().asSeconds() << std::endl;
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

void Chunk::regenMesh(bool regenNeighbours)
{
    if (regenNeighbours)
    {
        m_p_chunkMap->regenNeighboursSurrounding(m_location);
    }
    resetLight();
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

Chunk_Blocks& Chunk::getBlocks_nc()
{
    return m_blocks;
}

//This function is mostly for the sake of generating chunk meshes
const Chunk_Blocks* Chunk::getAdjBlocks(int xd, int zd) const
{
    Chunk* chunk = m_p_chunkMap->getChunkAt({m_location.x + xd, m_location.z + zd});
    if (chunk)
    {
        return &chunk->getBlocks();
    }
    return nullptr;
}

Chunk_Blocks* Chunk::getAdjBlocks(int xd, int zd)
{
    Chunk* chunk = m_p_chunkMap->getChunkAt({m_location.x + xd, m_location.z + zd});
    if (chunk)
    {
        return &chunk->getBlocks_nc();
    }
    return nullptr;
}

Chunk* Chunk::getChunkAdj(int dx, int dz) const
{
    return m_p_chunkMap->getChunkAt({m_location.x + dx, m_location.z + dz});
}

void Chunk::resetLight()
{
    m_blocks.resetLight();
}



uint8_t Chunk::getNaturalLight(const Block_Location& location) const
{
    auto x = location.x;
    auto z = location.z;
    auto y = location.y;

    if (location.x == -1 )
    {
        const auto* chunk =getChunkAdj(-1, 0);
        if (chunk)
        {
            return chunk->getNaturalLight({World_Constants::CHUNK_SIZE - 1, y, z});
        }
        return World_Constants::MAX_LIGHT_VALUE;
    }
    else if (location.z == -1 )
    {
        const auto* chunk =getChunkAdj(0, -1);
        if (chunk)
        {
            return chunk->getNaturalLight({x, y, World_Constants::CHUNK_SIZE - 1});
        }
        return World_Constants::MAX_LIGHT_VALUE;
    }
    else if (location.x == World_Constants::CHUNK_SIZE )
    {
        const auto* chunk =getChunkAdj(1, 0);
        if (chunk)
        {
            return chunk->getNaturalLight({0, y, z});
        }
        return World_Constants::MAX_LIGHT_VALUE;
    }
    else if (location.z == World_Constants::CHUNK_SIZE )
    {
        const auto* chunk =getChunkAdj(0, 1);
        if (chunk)
        {
            return chunk->getNaturalLight({x, y, 0});
        }
        return World_Constants::MAX_LIGHT_VALUE;
    }
    return m_blocks.getLayer(y).getNaturalLight(x, z);

}

uint8_t Chunk::getBlockLight(const Block_Location& location) const
{
    auto x = location.x;
    auto z = location.z;
    auto y = location.y;

    if (location.x == -1 )
    {
        const auto* chunk = getChunkAdj(-1, 0);
        if (chunk)
        {
            return chunk->getBlockLight({World_Constants::CHUNK_SIZE - 1, y, z});
        }
        return 0;
    }
    else if (location.z == -1 )
    {
        const auto* chunk =getChunkAdj(0, -1);
        if (chunk)
        {
            return chunk->getBlockLight({x, y, World_Constants::CHUNK_SIZE - 1});
        }
        return 0;
    }
    else if (location.x == World_Constants::CHUNK_SIZE )
    {
        const auto* chunk =getChunkAdj(1, 0);
        if (chunk)
        {
            return chunk->getBlockLight({0, y, z});
        }
        return 0;
    }
    else if (location.z == World_Constants::CHUNK_SIZE )
    {
        const auto* chunk =getChunkAdj(0, 1);
        if (chunk)
        {
            return chunk->getBlockLight({x, y, 0});
        }
        return 0;
    }
    return m_blocks.getLayer(y).getBlockLight(x, z);
}




void Chunk::saveToFile(const std::string& worldName) const
{
    if(!m_addedBlocks.empty())
    {
        std::ofstream outFile (getFileString(worldName) + ".chunk");

        for(auto& block : m_addedBlocks)
        {
            const Block_Location& l = block.first;

            outFile << "b " << l.x << " " << l.y << " " << l.z << " ";          //Block location
            outFile << (uint32_t)block.second->getData().getID() << std::endl;   //Block ID
        }
        outFile << "e";
    }
}

void Chunk::loadBlockData (const std::string& worldName)
{
    std::ifstream inFile(getFileString(worldName) + ".chunk");

    if(!inFile.is_open())
        return;

    int x = 0;
    int y = 0;
    int z = 0;
    int id = 0;

    char line;
    while(inFile >> line)
    {
        if (line == 'b')
        {
            inFile >> x >> y >> z >> id;
            addBlock({x, y, z}, Block::get((uint8_t)id));
        }
        else if (line == 'e')
        {
            break;
        }
    }

    for (auto& block : m_addedBlocks)
    {
        m_blocks.qSetBlock(block.first, (uint8_t)block.second->getData().getID());
    }
}


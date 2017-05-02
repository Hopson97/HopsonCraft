#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/Position_Conversion.h"

World::World(const Camera& camera, const World_Settings& worldSettings)
:   m_worldSettings (worldSettings)
,   m_p_camera      {&camera}
{
    for (int32_t x = 0 ; x < m_worldSettings.worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSettings.worldSize; z++)
        {
            m_chunks.addChunk({x, z}, *this, true);
        }
    }
}

void World::checkPlayerBounds(Player& player)
{
    if (player.position.x < 0.2)
    {
        player.position.x = 0.2;
    }
    if (player.position.z < 0.2)
    {
        player.position.z = 0.2;
    }

    if (player.position.x + 0.2 > m_worldSettings.worldSize * CHUNK_SIZE - 0.2 )
    {
        player.position.x = m_worldSettings.worldSize * CHUNK_SIZE - 0.3;
    }
    if (player.position.z + 0.2 > m_worldSettings.worldSize * CHUNK_SIZE - 0.2 )
    {
        player.position.z = m_worldSettings.worldSize * CHUNK_SIZE - 0.3;
    }
}

void World::setBlock(const Vector3& position, CBlock block)
{
    m_newBlocks.emplace_back(block, position);
}

CBlock World::getBlock(const Vector3& position)
{
    auto    chunkPosition   = Maths::worldToChunkletPos(position);
    auto    blockPosition   = Maths::blockToSmallBlockPos(Maths::worldToBlockPos(position));

    const auto& chunk = m_chunks.get(chunkPosition);

    return chunk->qGetBlock(blockPosition);
}

uint32_t World::getHeightAt(const Vector3& worldPosition)
{
    auto    chunkPosition   = Maths::worldToChunkPos(worldPosition);
    auto    blockPosition   = Maths::blockToSmallBlockPos(Maths::worldToBlockPos(worldPosition));

    const auto& chunk = m_chunks.get(chunkPosition);

    return chunk->getHeightAt(blockPosition.x, blockPosition.z);
}


void World::regenerateChunks()
{
    std::unordered_map<Chunk::Chunklet_Position, Chunk::Section*> chunksToUpdate;

    //Duh, inserts a chunk into the map..
    auto insertChunk = [&](const Chunk::Chunklet_Position& chunkPosition,
                                 Chunk::Section* chunk)
    {
        const auto& chunkFull = m_chunks.get({chunkPosition.x, chunkPosition.z});
        if(!chunkFull)
            return;

        while (!chunk)
        {
            chunkFull->addSection();
            chunk = chunkFull->getSection(chunkPosition.y);
        }
        chunksToUpdate.insert(std::make_pair(chunkPosition, chunk));
    };

    //Lambda checks if blocks are being set on chunk edges, and if so, adds the adjacent chunk to the update batch
    auto checkForBatchAdd = [&](int8_t position,
                                const Chunk::Chunklet_Position& chunkPosition,
                                const Vector3& direction)
    {
        if (position == 0)
        {
            Chunk::Chunklet_Position newChunkPosition(chunkPosition.x - direction.x,
                                                      chunkPosition.y - direction.y,
                                                      chunkPosition.z - direction.z);

            insertChunk(newChunkPosition, m_chunks.get(newChunkPosition));
        }
        else if (position == CHUNK_SIZE - 1)
        {
            Chunk::Chunklet_Position newChunkPosition(chunkPosition.x + direction.x,
                                                      chunkPosition.y + direction.y,
                                                      chunkPosition.z + direction.z);

            insertChunk(newChunkPosition, m_chunks.get(newChunkPosition));
        }
    };



    for (New_Block& newBlock : m_newBlocks)
    {
        //Get respective positions and objects
        auto    chunkPosition   = Maths::worldToChunkletPos(newBlock.position);
        auto    blockPosition   = Maths::blockToSmallBlockPos(Maths::worldToBlockPos(newBlock.position));
        const auto& chunkFull   = m_chunks.get({chunkPosition.x, chunkPosition.z});

        Chunk::Section*             chunk           = nullptr;

        //Adds sections onto a chunk until it reaches the height of the block
        while (!chunk)
        {
            chunkFull->addSection();
            chunk = chunkFull->getSection(chunkPosition.y);
        }


        //Set block
        chunk->qSetBlock(blockPosition, newBlock.block);

        //Insert chunks into a regeneration map
        insertChunk(chunkPosition, chunk);
        checkForBatchAdd(blockPosition.x, chunkPosition, {1, 0, 0});
        checkForBatchAdd(blockPosition.y, chunkPosition, {0, 1, 0});
        checkForBatchAdd(blockPosition.z, chunkPosition, {0, 0, 1});
    }

    //Regenerate chunks
    for (auto& chunk : chunksToUpdate)
    {
        Chunk::Section* sect = chunk.second;
        sect->makeMesh();
    }

    m_newBlocks.clear();
}

//Generates meshes for the chunks.
//It does this in a sort of radius starting from the middle of the world
void World::buffer(const Camera& camera)
{
    if (m_loadingDistance == ((m_worldSettings.worldSize / 2) + 1)) return;

    auto minDis = m_worldSettings.worldSize / 2 - m_loadingDistance;
    auto maxDis = m_worldSettings.worldSize / 2 + m_loadingDistance;

    auto isMeshMade = false;

    //std::cout << m_loadingDistance << std::endl;

    for (int32_t x = minDis ; x < maxDis; x++)
    {
        for (int32_t z = minDis; z < maxDis; z++)
        {
            Chunk::Full_Chunk* chunk = m_chunks.get({x, z});
            if (chunk)
            {
                if(chunk->tryGen(*m_p_camera))
                {
                    isMeshMade = true;
                    break;
                }
            }
        }
        if (isMeshMade)
        {
            break;
        }
    }
    if (!isMeshMade)
    {
        m_loadingDistance++;
    }
}

void World::draw(Renderer::Master& renderer, const Camera& camera)
{
    m_facesDrawn = 0;
    for (auto& chunk : m_chunks.getChunks())
    {
        m_facesDrawn += chunk.second.draw(renderer, camera);
    }
}

void World::drawWorld(Renderer::Master& renderer, const Camera& camera)
{
    if (!m_newBlocks.empty())
        regenerateChunks();

    draw(renderer, camera);
    buffer(camera);
}

const World_Settings& World::getWorldSettings() const
{
    return m_worldSettings;
}


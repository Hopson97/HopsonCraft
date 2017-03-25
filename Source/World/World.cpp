#include "World.h"

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"

#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/General_Maths.h"

World::World(const Camera& camera, int32_t worldSize)
:   m_p_camera      (&camera)
,   m_worldSize     (worldSize)
{
    for (int32_t x = 0 ; x < m_worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSize; z++)
        {
            m_chunks.addChunk({x, z}, *this);
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

    if (player.position.x + 0.2 > m_worldSize * CHUNK_SIZE - 0.2 )
    {
        player.position.x = m_worldSize * CHUNK_SIZE - 0.3;
    }
    if (player.position.z + 0.2 > m_worldSize * CHUNK_SIZE - 0.2 )
    {
        player.position.z = m_worldSize * CHUNK_SIZE - 0.3;
    }
}

void World::setBlock(const Vector3& position, CBlock block)
{
    m_newBlocks.emplace_back(block, position);
}

void World::updateChunks()
{
    std::unordered_map<Chunk::Chunklet_Position, Chunk::Section*> chunksToUpdate;
    for (New_Block& newBlock : m_newBlocks)
    {
        Chunk::Chunklet_Position    chunkPosition   = Maths::worldToChunkletPos(newBlock.position);
        Block::Small_Position       blockPosition   = Maths::blockToSmallBlockPos(Maths::worldToBlockPos(newBlock.position));
        Chunk::Section*             chunk           = m_chunks.get(chunkPosition);

        chunk->qSetBlock(blockPosition, newBlock.block);
        chunksToUpdate.insert(std::make_pair(chunkPosition, chunk));
    }

    for (auto& chunk : chunksToUpdate)
    {
        Chunk::Section* sect = chunk.second;
        sect->makeMesh();
    }
}


void World::buffer(const Camera& camera)
{
    bool isMeshMade = false;
    for (int32_t x = 0 ; x < m_worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSize; z++)
        {
            Chunk::Full_Chunk* chunk = m_chunks.get({x, z});
            if (chunk)
            {
                if(chunk->tryGen(camera))
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
}

void World::draw(Renderer::Master& renderer, const Camera& camera)
{
    m_facesDrawn = 0;
    for (int32_t x = 0 ; x < m_worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSize; z++)
        {
            Chunk::Full_Chunk* chunk = m_chunks.get({x, z});
            if (chunk)
            {
                m_facesDrawn += chunk->draw(renderer, camera);
            }
        }
    }
}



void World::drawWorld(Renderer::Master& renderer, const Camera& camera)
{
    updateChunks();
    draw(renderer, camera);
    buffer(camera);
}

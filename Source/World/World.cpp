#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/Position_Conversion.h"

#include "../Util/STD_Util.h"

World::World(const World_Settings& worldSettings, const Camera& camera)
:   m_worldGen      (m_chunks, m_deleteMutex, worldSettings, camera, m_deleteChunks)
,   m_worldSettings (worldSettings)
,   m_chunks        (*this)
,   m_pCamera       (&camera)
{
    int32_t centre = 20000;
    int size = 2;
    for (int x = -size ; x <= size; x++)
    {
        for (int z = -size; z <= size; z++)
        {
            m_chunks.addChunk({centre + x, centre + z}, true);
        }
    }

   // m_worldGen.launch();

    //See "World_Gen.cpp"
    for (int i = 0; i < 1; i++)
    {
        m_threads.emplace_back([&]()
        {
            while (m_isRunning)
            {
                generateWorld(*m_pCamera);
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
        });
    }
}


World::~World()
{
    m_isRunning = false;
    for (auto& thread : m_threads)
    {
        thread.join();
    }
}

void World::updateChunks(const Player& player)
{
    if (!m_newBlocks.empty())
    {
        regenerateChunks();
    }
    if (!m_triggerBlocks.empty())
    {
        triggerBlocks();
    }
    m_state = State::Nothing;

    for (auto itr = m_chunks.getChunks().begin(); itr != m_chunks.getChunks().end(); itr++)
    {
        Chunk::Full_Chunk& chunk = itr->second;
        chunk.tick();
    }

    if (!m_deleteChunks.empty())
    {
        m_deleteMutex.lock();
        for (auto& chunkLocation : m_deleteChunks)
        {
            m_chunks.deleteChunk(chunkLocation);
        }
        m_deleteChunks.clear();
        m_deleteMutex.unlock();
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
}

void World::qSetBlock(const Vector3& position, CBlock block)
{
    setBlock(position, block);
}

void World::setBlock(const Vector3& position, CBlock block)
{
    if (position.y < 1)
    {
        return;
    }   //Do not allow block breaking at the bottom of the world

    std::cout << "Set " << block.getData().name << " at "   << (int)position.x
                                                << " "      << (int)position.y
                                                << " "      << (int)position.z << "\n";

    m_newBlocks.emplace_back(block, position);

    for (int y = -1; y <= 1; ++y)
    for (int x = -1; x <= 1; ++x)
    for (int z = -1; z <= 1; ++z)
    {
        if (x == 0 &&
            z == 0 &&
            y == 0)
        {
            continue;
        }

        auto pos = position + Vector3{x, y, z};
        switch(m_state)
        {
            case State::Triggering:
                if (!existsInMap(m_triggerBlocks, pos) && !existsInMap(m_sheduledTriggerBlocks, pos))
                {
                    m_sheduledTriggerBlocks.emplace(std::make_pair(pos, getBlock(pos)));
                }
                break;

            default:
                if (!existsInMap(m_triggerBlocks, pos) && !existsInMap(m_sheduledTriggerBlocks, pos))
                {
                    m_triggerBlocks.emplace(std::make_pair(pos, getBlock(pos)));
                }
                break;
        }
    }
}

CBlock World::getBlock(const Vector3& position)
{
    auto chunkPos = Maths::worldToChunkPos(position);

    if (m_chunks.existsAt(chunkPos))
    {
        auto blockPosition = Maths::worldToBlockPos(position);
        return m_chunks.get(chunkPos).qGetBlock(blockPosition);
    }
    else
    {
        return Block::ID::Air;
    }
}

uint32_t World::getHeightAt(const Vector3& worldPosition)
{
    auto    chunkPosition   = Maths::worldToChunkPos(worldPosition);
    auto    blockPosition   = Maths::blockToSmallBlockPos(Maths::worldToBlockPos(worldPosition));

    const auto& chunk = m_chunks.get(chunkPosition);

    return chunk.getHeightAt(blockPosition.x, blockPosition.z);
}


void World::regenerateChunks()
{
    m_state = State::Regenerating;
    std::unordered_map<Chunk::Chunklet_Position, Chunk::Section*> chunksToUpdate;

    //Duh, inserts a chunk into the map..
    auto insertChunk = [&](const Chunk::Chunklet_Position& chunkPosition,
                                 Chunk::Section* chunk)
    {
        auto& chunkFull = m_chunks.get({chunkPosition.x, chunkPosition.z});

        while (!chunk)
        {
            chunkFull.addSection();
            chunk = chunkFull.getSection(chunkPosition.y);
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

    //Lambda's end above, function technically begins here
    for (auto& newBlock : m_newBlocks)
    {
        //Get respective positions and objects
        auto    chunkPosition   = Maths::worldToChunkletPos(newBlock.position);
        auto    blockPosition   = Maths::blockToSmallBlockPos(Maths::worldToBlockPos(newBlock.position));
        auto&   chunkFull       = m_chunks.get({chunkPosition.x, chunkPosition.z});

        Chunk::Section* chunk = nullptr;

        //Adds sections onto a chunk until it reaches the height of the block
        while (!chunk)
        {
            chunkFull.addSection();
            chunk = chunkFull.getSection(chunkPosition.y);
        }


        //Set block
        chunk->qSetBlock(blockPosition, newBlock.block);

        //Insert chunks into a regeneration map
        insertChunk(chunkPosition, chunk);
        //Check neighbours of this chunk, and then add those into regeneration queue thing
        checkForBatchAdd(blockPosition.x, chunkPosition, {1, 0, 0});
        checkForBatchAdd(blockPosition.y, chunkPosition, {0, 1, 0});
        checkForBatchAdd(blockPosition.z, chunkPosition, {0, 0, 1});
    }

    //Regenerate chunks
    for (auto& chunk : chunksToUpdate)
    {
        Chunk::Section* sect = chunk.second;
        sect->makeMesh();
        sect->bufferMesh();
    }

    m_newBlocks.clear();
}

void World::triggerBlocks()
{
    m_state = State::Triggering;
    for (auto& block : m_triggerBlocks)
    {
        auto& p = block.first;
        block.second.getType().trigger(*this, {int(p.x),
                                              int(p.y),
                                              int(p.z)});
    }
    /*
     *  When blocks are triggered, they have potential to trigger yet more blocks.
     *  Usually, you would just clear the triggered blocks here
     *  But, this would cause the blocks that get triggered during the triggering of blocks to not get
     *  triggered, because the std::vector would be cleared.
     *
     *   So, instead, I add them into a different std::vector if the block is triggered during this
     *   state of the world (State::Triggering)
     */
    m_triggerBlocks = std::move(m_sheduledTriggerBlocks);
}


void World::drawWorld(Renderer::Master& renderer, const Camera& camera)
{
    m_facesDrawn = 0;
    for (auto& chunk : m_chunks.getChunks())
    {
        if (chunk.second.hasGeneratedBlockData)
            m_facesDrawn += chunk.second.draw(renderer, camera);
    }
}

const World_Settings& World::getWorldSettings() const
{
    return m_worldSettings;
}

AABB World::getBlockAABB(const Block::Position& position)
{
    AABB blockAABB({1.2, 1.2, 1.2});
    blockAABB.update({position.x - 0.1, position.y - 0.1, position.z - 0.1});
    return blockAABB;
}

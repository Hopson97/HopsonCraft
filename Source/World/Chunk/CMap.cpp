#include "CMap.h"

#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>

#include "../../Camera.h"
#include "../../Renderer/RMaster.h"
#include "Chunklet.h"

#include "../../Maths/General_Maths.h"
#include "../../Maths/Matrix_Maths.h"
#include "../../Maths/Frustum.h"


namespace Chunk
{
    Map::Map(const Camera& camera, World_File& file)
    :   m_p_camera      (&camera)
    ,   m_p_worldFile   (&file)
    ,   m_isRunning     (true)
    {
        addChunk(Maths::worldToChunkPos(camera.position));

        m_chunkGenThreads.push_back(std::make_unique<std::thread>([&]()
        {
            while (m_isRunning)
            {
                manageChunks();
            }
        }));
    }

    Map::~Map()
    {
        m_isRunning = false;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        for(auto& thread : m_chunkGenThreads)
            thread->join();
    }

    void Map::update()
    {
        m_regenerator.regen();

        if (!m_chunksToDelete.empty())
        {
            std::lock_guard<std::mutex> lock(m_deleteChunkMutex);
            for (auto& position : m_chunksToDelete)
            {
                m_chunks.erase(position);
            }
            m_chunksToDelete.clear();
        }
    }


    void Map::draw(Renderer::Master& renderer, const Camera& camera)
    {
        bool shouldBuffer = true;

        for (auto& chunk : m_chunks)
        {
            if (camera.getFrustum().pointInFrustum(chunk.second->getWorldPosition()))
            //if (camera.getFrustum().boxInFrustum(chunk.second->getAABB()))
            {
                shouldBuffer = !chunk.second->draw(renderer, shouldBuffer);
            }
        }
    }

    void Map::addChunk(const Position& position)
    {
        m_addChunkMutex.lock();
        if(!getChunk(position))
        {
            m_chunks.insert(std::make_pair
                           (position, std::make_unique<Column>(position, *this, m_regenerator, *m_p_worldFile)));
        }
        m_addChunkMutex.unlock();
    }

    Column* Map::getChunk(const Chunk::Position& position)
    {
        if (m_chunks.find(position) == m_chunks.end())
        {
            return nullptr;
        }
        return m_chunks.at(position).get();
    }

    const Column* Map::getChunk(const Chunk::Position& position) const
    {
        if (m_chunks.find(position) == m_chunks.end())
        {
            return nullptr;
        }
        return m_chunks.at(position).get();
    }

    CBlock Map::getBlockAt(const Vector3& worldPosition)
    {
        const auto* chunk = getChunk(Maths::worldToChunkPos(worldPosition));
        if(chunk)
        {
            auto blockPosition = Maths::worldToBlockPos(worldPosition);
            return chunk->getBlock(blockPosition);
        }
        else
        {
            return Block::ID::Air;
        }
    }

    void Map::breakBlock(const Vector3& worldPosition)
    {
        auto* chunk = getChunk(Maths::worldToChunkPos(worldPosition));
        if(chunk)
        {
            auto blockPosition = Maths::worldToBlockPos(worldPosition);
            triggerBlocks(blockPosition);
            chunk->setBlock(blockPosition, Block::ID::Air);
        }
    }

    void Map::placeBlock(const Vector3& worldPosition, CBlock block)
    {
        auto* chunk = getChunk(Maths::worldToChunkPos(worldPosition));
        if(chunk)
        {
            auto blockPosition = Maths::worldToBlockPos(worldPosition);
            //triggerBlocks(blockPosition);
            chunk->setBlock(blockPosition, block);
        }
    }

    void Map::triggerBlocks(const Block::Column_Position& worldPosition)
    {
        for (int32_t y = -1; y <= 1; y++)
        {
            for (int32_t x = -1; x <= 1; x++)
            {
                for (int32_t z = -1; z <= 1; z++)
                {
                }
            }
        }
    }






}   //Namespace Chunk












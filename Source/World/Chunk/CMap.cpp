#include "CMap.h"

#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>

#include "../../Camera.h"
#include "../../Renderer/RMaster.h"
#include "Chunklet.h"

#include "../../Maths/General_Maths.h"


namespace Chunk
{
    Map::Map(const Camera& camera)
    :   m_p_camera  (&camera)
    ,   m_isRunning (true)
    {
        for(int i = 0; i < 1 ; i++)
        {
            m_chunkGenThreads.push_back(std::make_unique<std::thread>([&]() { manageChunks(); }));
        }
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
        for (auto itr = m_chunks.begin(); itr != m_chunks.end();)
        {
            Column& c = *(itr)->second;
            c.update();

            if(c.getFlags().deleteMe)
            {
                itr = m_chunks.erase(itr);
            }
            else
            {
                itr++;
            }
        }
    }

    void Map::draw(Renderer::Master& renderer)
    {
        for (auto& chunk : m_chunks)
        {
            chunk.second->draw(renderer);// renderer.draw(*chunk.second);
        }
    }

    void Map::addChunk(const Position& position)
    {
        m_addChunkMutex.lock();
        if(!getChunk(position))
        {
            m_chunks.insert(std::make_pair
                           (position, std::make_unique<Column>(position, *this)));
        }
        m_addChunkMutex.unlock();
    }

    Column* Map::getChunk(const Chunk::Position& position)
    {
        if (m_chunks.find(position) == m_chunks.end())
            return nullptr;
        return m_chunks.at(position).get();
    }

    const Column* Map::getChunk(const Chunk::Position& position) const
    {
        if (m_chunks.find(position) == m_chunks.end())
            return nullptr;
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
            chunk->setBlock(blockPosition, Block::ID::Air);
        }
    }




}   //Namespace Chunk












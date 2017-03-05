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
    ,   m_chunkLoadThread   ([&](){manageChunks();})
    { }

    Map::~Map()
    {
        m_isRunning = false;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        m_chunkLoadThread.join();
    }

    void Map::update()
    {
        for (auto itr = m_chunks.begin(); itr != m_chunks.end();)
        {
            Column& c = *(itr)->second;
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

    void Map::addChunk(const Position& pos)
    {
        if(!getChunklet(pos))
        {
            m_chunks.insert(std::make_pair
                           (pos, std::make_unique<Column>(pos, *this)));
        }
    }

    Column* Map::getChunklet(const Chunk::Position& pos)
    {
        if (m_chunks.find(pos) == m_chunks.end())
        {
            return nullptr;
        }
        else
        {
            return m_chunks.at(pos).get();
        }
    }

    const Column* Map::getChunklet(const Chunk::Position& pos) const
    {
        if (m_chunks.find(pos) == m_chunks.end())
        {
            return nullptr;
        }
        else
        {
            return m_chunks.at(pos).get();
        }
    }

    struct Load_Sector
    {
        Load_Sector(int32_t minX, int32_t maxX,
                    int32_t minZ, int32_t maxZ)
        :   minX    (minX)
        ,   maxX    (maxX)
        ,   minZ    (minZ)
        ,   maxZ    (maxZ)
        {

        }

        int32_t minX, maxX,
                minZ, maxZ;
    };

    void Map::manageChunks()
    {
        while (m_isRunning)
        {
            loadAndGenChunks();

            if (m_currentLoadDist < m_renderDistance - 1)
                m_currentLoadDist++;
            else
                m_currentLoadDist = 2;


            flagChunks();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Map::loadAndGenChunks()
    {
        auto pos = Maths::worldToChunkPos(m_p_camera->position);
        Load_Sector sect
        (
            pos.x - m_currentLoadDist,
            pos.x + m_currentLoadDist,
            pos.y - m_currentLoadDist,
            pos.y + m_currentLoadDist
        );
        for (auto x = sect.minX; x < sect.maxX; x++)
        {
            for (auto z = sect.minZ; z < sect.maxZ; z++)
            {
                addChunk({x, z});
            }
        }
        for (auto x = sect.minX; x < sect.maxX; x++)
        {
            for (auto z = sect.minZ; z < sect.maxZ; z++)
            {
                auto* chunk =  getChunklet({x, z});
                if (chunk)
                {
                    if (!chunk->getFlags().hasFullMesh)
                    {
                        chunk->createFullMesh();
                    }
                }
            }
        }
    }

    void Map::flagChunks()
    {
        auto pos = Maths::worldToChunkPos(m_p_camera->position);
         Load_Sector deleteSect
         (
             pos.x - m_renderDistance - 1,
             pos.x + m_renderDistance + 1,
             pos.y - m_renderDistance - 1,
             pos.y + m_renderDistance + 1
         );

         for (auto itr = m_chunks.begin(); itr != m_chunks.end(); itr++)
         {
             auto& c = *itr->second;
             Position p = c.getPosition();
             if (p.x < deleteSect.minX ||
                 p.x > deleteSect.maxX ||
                 p.y < deleteSect.minZ ||
                 p.y > deleteSect.maxZ)
             {
                 c.setDeleteFlag(true);
             }
         }
    }





}   //Namespace Chunk

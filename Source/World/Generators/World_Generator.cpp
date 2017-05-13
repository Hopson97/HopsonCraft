#include "World_Generator.h"

#include <iostream>

#include "../World_Settings.h"
#include "../World_Settings.h"

#include "../Chunk/CMap.h"

#include "../../Camera.h"

#include "../../Maths/Position_Conversion.h"

World_Generator::World_Generator(Chunk::Map& chunkMap,
                                 std::mutex& deleteMutex,
                                 const World_Settings& settings,
                                 const Camera& camera,
                                 std::vector<Chunk::Position>& deleteChunks)
:   m_pCamera           (&camera)
,   m_pWorldSettings    (&settings)
,   m_pChunkMap         (&chunkMap)
,   m_pDeleteMutex      (&deleteMutex)
,   m_pDeleteChunks     (&deleteChunks)
{}



World_Generator::~World_Generator()
{
    m_isRunning = false;
    for (auto& thread : m_workers)
    {

        thread.join();
    }

}
/*
void World_Generator::launch()
{
    m_workers.emplace_back([&]()
    {
        while (m_isRunning)
        {
            generateWorld();
        }
    });
}

void World_Generator::generateWorld()
{
    if (m_loadingDistance == ((m_pWorldSettings->worldSize / 2) + 1))
    {
        m_loadingDistance = 1;
    }

    auto cameraPosition = Maths::worldToChunkPos(m_pCamera->position);

    int32_t minDisX = 0;
    int32_t maxDisX = 0;

    int32_t minDisZ = 0;
    int32_t maxDisZ = 0;

    bool isMeshMade = false;

    for (int i = 0; i < m_loadingDistance; i++)
    {
        m_pDeleteMutex->unlock();
        if (m_pWorldSettings->isInfiniteTerrain)
        {
            minDisX = cameraPosition.x - i;
            maxDisX = cameraPosition.x + i;

            minDisZ = cameraPosition.y - i;
            maxDisZ = cameraPosition.y + i;
        }
        else
        {
            int32_t minDis = m_pWorldSettings->worldSize / 2 - m_loadingDistance;
            int32_t maxDis = m_pWorldSettings->worldSize / 2 + m_loadingDistance;

            minDisX = minDis;
            maxDisX = maxDis;

            minDisZ = minDis;
            maxDisZ = maxDis;

        }
        m_pDeleteMutex->lock();
        for (int32_t x = minDisX; x < maxDisX; x++)
        {
            for (int32_t z = minDisZ; z < maxDisZ; z++)
            {
                Chunk::Position position(x, z);
                if(!m_pChunkMap->existsAt(position))
                {
                    m_pChunkMap->addChunk(position, true);
                }

                Chunk::Full_Chunk* chunk = m_pChunkMap->get({x, z});

                if(chunk->tryGen(*m_pCamera))
                {
                    isMeshMade = true;
                    break;
                }
            }
            if (isMeshMade)
            {
                break;
            }
        }
    }

    if (!isMeshMade)
    {
        m_loadingDistance++;
    }
    if (m_pWorldSettings->isInfiniteTerrain)
    {
        int minX = cameraPosition.x - m_pWorldSettings->worldSize / 2 - 1;
        int maxX = cameraPosition.x + m_pWorldSettings->worldSize / 2 + 1;
        int minZ = cameraPosition.y - m_pWorldSettings->worldSize / 2 - 1;
        int maxZ = cameraPosition.y + m_pWorldSettings->worldSize / 2 + 1;

        for(auto& chunk : m_pChunkMap->getChunks())
        {
            Chunk::Full_Chunk& c = chunk.second;
            auto location = c.getPosition();

            //Check bounds
            if (location.x <= minX ||
                location.x >= maxX ||
                location.y <= minZ ||
                location.y >= maxZ)
            {
                //If the chunk is outside of the bounds of the render distance, then add the position of it into a delete vector
                if (!c.hasDeleteFlag)
                {
                    c.hasDeleteFlag = true;
                    m_pDeleteChunks->push_back(location);
                }
            }
        }
    }

    m_pDeleteMutex->unlock();
}
*/

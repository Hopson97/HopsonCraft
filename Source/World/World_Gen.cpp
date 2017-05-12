#include "World.h"

#include "../Renderer/RMaster.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/Position_Conversion.h"


//Generates meshes for the chunks.
//It does this in a sort of radius starting from the middle of the world
//This is ran concurrently alongside the main render/ update thread
void World::generateWorld(const Camera& camera)
{
    if (m_loadingDistance == ((m_worldSettings.worldSize / 2) + 1))
    {
        m_loadingDistance = 1;
    }

    m_cameraPosition = Maths::worldToChunkPos(camera.position);

    int32_t minDisX = 0;
    int32_t maxDisX = 0;

    int32_t minDisZ = 0;
    int32_t maxDisZ = 0;

    bool isMeshMade = false;

    m_deleteMutex.lock();
    for (int i = 0; i < m_loadingDistance; i++)
    {
        m_deleteMutex.unlock();
        if (m_worldSettings.isInfiniteTerrain)
        {
            minDisX = m_cameraPosition.x - i;
            maxDisX = m_cameraPosition.x + i;

            minDisZ = m_cameraPosition.y - i;
            maxDisZ = m_cameraPosition.y + i;
        }
        else
        {
            int32_t minDis = m_worldSettings.worldSize / 2 - m_loadingDistance;
            int32_t maxDis = m_worldSettings.worldSize / 2 + m_loadingDistance;

            minDisX = minDis;
            maxDisX = maxDis;

            minDisZ = minDis;
            maxDisZ = maxDis;

        }
        m_deleteMutex.lock();
        for (int32_t x = minDisX; x < maxDisX; x++)
        {
            for (int32_t z = minDisZ; z < maxDisZ; z++)
            {
                Chunk::Position position(x, z);
                if(!m_chunks.existsAt(position))
                {
                    m_chunks.addChunk(position, true);
                }

                Chunk::Full_Chunk* chunk = m_chunks.get({x, z});

                if(chunk->tryGen())
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
    if (m_worldSettings.isInfiniteTerrain)
    {
        int minX = m_cameraPosition.x - m_worldSettings.worldSize / 2 - 1;
        int maxX = m_cameraPosition.x + m_worldSettings.worldSize / 2 + 1;
        int minZ = m_cameraPosition.y - m_worldSettings.worldSize / 2 - 1;
        int maxZ = m_cameraPosition.y + m_worldSettings.worldSize / 2 + 1;

        for(auto& chunk : m_chunks.getChunks())
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
                    m_deleteChunks.push_back(location);
                }
            }
        }
    }

    m_deleteMutex.unlock();
}

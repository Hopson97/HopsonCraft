#include "World.h"

#include "../Renderer/RMaster.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/Position_Conversion.h"

struct Area
{
    struct Vec2
    {
        Vec2() = default;
        Vec2(int ix, int iz)
        :   x   (ix)
        ,   z   (iz)
        { }

        int x, z;
    };

    Vec2 minPoint, maxPoint;
};

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

    Area area;
    bool isMeshMade = false;

    for (int i = 0; i < m_loadingDistance; i++)
    {
        m_deleteMutex.unlock();
        if (m_worldSettings.isInfiniteTerrain)
        {
            area.minPoint = {m_cameraPosition.x - i,
                             m_cameraPosition.y - i};

            area.maxPoint = {m_cameraPosition.x + i,
                             m_cameraPosition.y + i};
        }
        else
        {
            int32_t minDis = m_worldSettings.worldSize / 2 - m_loadingDistance;
            int32_t maxDis = m_worldSettings.worldSize / 2 + m_loadingDistance;

            area.minPoint = {minDis,
                             minDis};

            area.maxPoint = {maxDis,
                             maxDis};

        }
        m_deleteMutex.lock();
        for (int32_t x = area.minPoint.x; x < area.maxPoint.x; x++)
        {
            for (int32_t z = area.minPoint.z; z < area.maxPoint.z; z++)
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
        Area bounds;
        bounds.minPoint = { m_cameraPosition.x - m_worldSettings.worldSize / 2 - 1,
                            m_cameraPosition.y - m_worldSettings.worldSize / 2 - 1};

        bounds.maxPoint = { m_cameraPosition.x + m_worldSettings.worldSize / 2 + 1,
                            m_cameraPosition.y + m_worldSettings.worldSize / 2 + 1};

        for(auto& chunk : m_chunks.getChunks())
        {
            Chunk::Full_Chunk& c = chunk.second;
            auto location = c.getPosition();

            //Check bounds
            if (location.x <= bounds.minPoint.x ||
                location.x >= bounds.maxPoint.x ||
                location.y <= bounds.minPoint.z ||
                location.y >= bounds.maxPoint.z)
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

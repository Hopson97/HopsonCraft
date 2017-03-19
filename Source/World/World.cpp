#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"

World::World(const Camera& camera, uint32_t worldSize)
:   m_p_camera      (&camera)
,   m_worldSize     (worldSize)
{ }

void World::checkPlayerBounds(Player& player)
{

}

void World::drawWorld(Renderer::Master& renderer)
{
    bool isMeshMade = false;
    for (int32_t x = 0 ; x < m_worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSize; z++)
        {
            if (m_chunkSection.find({x, z}) == m_chunkSection.end())
            {
                m_chunkSection.insert(std::make_pair(Chunk::Position{x, z}, std::make_unique<Chunk::Section>(Chunk::Chunklet_Position(x, 0, z))));
                isMeshMade = true;
                break;
            }
            else
            {
                renderer.draw(*m_chunkSection.at({x, z}));
            }
        }
        if (isMeshMade)
        {
            break;
        }
    }
}

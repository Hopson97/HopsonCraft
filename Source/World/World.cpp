#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"
#include "../Maths/General_Maths.h"

#include "../Camera.h"
#include "../Player.h"

#include "../Physics/Ray.h"

#include "../Util/Random.h"

World::World(const Camera& camera, Player& player)
:   m_chunkMap      (camera)
,   m_blockEditor   (m_chunkMap)
,   m_p_player      (&player)
{ }

void World::input(Camera& camera)
{
    //testRayCastBlockEdit();
    m_blockEditor.input(*m_p_player);
}

void World::update(float dt)
{
    m_chunkMap.update();
}

void World::draw(Renderer::Master& renderer)
{
    m_chunkMap.draw(renderer);
}

void World::testRayCastBlockEdit()
{
    static sf::Clock timer;

    auto& rot = m_p_player->rotation;
    auto& pos = m_p_player->position;

    auto lastRayPosition = m_p_player->position;

    Ray raycast (rot.y + 90,
                 rot.x,
                 pos);

    for (uint32_t i = 0; i < 6 / 0.1; i++)
    {
        raycast.step(0.1);

        CBlock b = m_chunkMap.getBlockAt(raycast.getEndPoint());

        if(b.id == Block::ID::Air)
        {
            continue;
        }
        else
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                timer.getElapsedTime().asSeconds() >= 0.5)
            {
                m_chunkMap.breakBlock(raycast.getEndPoint());
                timer.restart();
            }
        }
        lastRayPosition = raycast.getEndPoint();
    }
}































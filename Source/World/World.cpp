#include "World.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

#include "../Renderer/RMaster.h"
#include "../Maths/General_Maths.h"

#include "../Camera.h"
#include "../Player.h"

#include "../Util/Random.h"

World::World(const Camera& camera, Player& player)
:   m_chunkMap  (camera)
,   m_p_player  (&player)
{

}

void World::input(Camera& camera)
{
    m_p_player->addForce(camera.getVelocity());
    camera.position = m_p_player->position;
}

void World::update(float dt)
{
    m_chunkMap.update();
}

void World::draw(Renderer::Master& renderer)
{
    m_chunkMap.draw(renderer);
}

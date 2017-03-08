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
    m_blockEditor.input(*m_p_player);
}

void World::update(float dt)
{
    m_chunkMap.update();

    m_p_player->testForCollide(m_chunkMap, dt);
    m_p_player->update(dt);
}

void World::draw(Renderer::Master& renderer)
{
    m_chunkMap.draw(renderer);
}








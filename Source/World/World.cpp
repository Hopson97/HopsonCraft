#include "World.h"

#include <SFML/Window/Event.hpp>

#include "../Maths/Position_Converter_Maths.h"
#include "../Renderer/Master_Renderer.h"

World::World(uint32_t seed,
            const std::string& name)
:   m_player()
,   m_playerLocation(Maths::worldToChunkPosition(m_player.getCamera().position))
,   m_name  (name)
,   m_chunkMap  (m_playerLocation, name, seed)
{

}

void World::input(sf::Event& e)
{

}

void World::input()
{

}

void World::update(float dt)
{

}

void World::draw(Master_Renderer& renderer)
{

}

#include "World.h"

#include "../Renderer/RMaster.h"

World::World()
{

}

void World::input(Camera& camera)
{

}

void World::update(float dt)
{

}

void World::draw(Renderer::Master& renderer)
{
    renderer.draw(m_chunklet);
}

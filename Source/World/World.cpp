#include "World.h"

#include "../Renderer/RMaster.h"

World::World(const Camera& camera)
:   m_chunkMap  (camera)
{

}

void World::input(Camera& camera)
{

}

void World::update(float dt)
{
    m_chunkMap.update();
}

void World::draw(Renderer::Master& renderer)
{
    m_chunkMap.draw(renderer);
}

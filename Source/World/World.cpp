#include "World.h"

#include <iostream>

#include "../Renderer/RMaster.h"
#include "../Maths/General_Maths.h"

#include "../Camera.h"

World::World(const Camera& camera)
:   m_chunkMap  (camera)
{

}

void World::input(Camera& camera)
{
    /*
    Chunk::Column* c = m_chunkMap.getChunklet(Maths::worldToChunkPos(camera.position));
    if(c)
    {
        auto bp = Maths::worldToBlockPos(camera.position);
        if(c->getBlock(bp) != 0)
        {
            std::cout << "Gay" << std::endl;
        }
    }
    */
}

void World::update(float dt)
{
    m_chunkMap.update();
}

void World::draw(Renderer::Master& renderer)
{
    m_chunkMap.draw(renderer);
}

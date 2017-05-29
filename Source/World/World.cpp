#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/Position_Conversion.h"

#include "../Util/STD_Util.h"

World::World(const World_Settings& worldSettings, const Camera& camera)
:   m_worldSettings (worldSettings)
,   m_pCamera       (&camera)
{

}


World::~World()
{

}

void World::updateChunks(const Player& player)
{

}


void World::checkPlayerBounds(Player& player)
{
    if (player.position.x < 0.2)
    {
        player.position.x = 0.2;
    }
    if (player.position.z < 0.2)
    {
        player.position.z = 0.2;
    }
}

void World::setBlock (int x, int y, int z, CBlock block)
{

}


CBlock World::getBlock (int x, int y, int z) const
{

}

uint32_t World::getHeightAt(const Vector3& worldPosition)
{
    return 0;
}


void World::regenerateChunks()
{

}

void World::triggerBlocks()
{

}


void World::drawWorld(Renderer::Master& renderer, const Camera& camera)
{

}

const World_Settings& World::getWorldSettings() const
{
    return m_worldSettings;
}

AABB World::getBlockAABB(const Block::Position& position)
{
    AABB blockAABB({1.0, 1.0, 1.0});
    blockAABB.update({position.x, position.y, position.z});
    return blockAABB;
}


//Generates meshes for the chunks.
//It does this in a sort of radius starting from the middle of the world
//This is ran concurrently alongside the main render/ update thread
void World::generateWorld(const Camera& camera)
{

}


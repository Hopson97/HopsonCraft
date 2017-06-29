#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/PositionConversion.h"
#include "Chunk/Nodes.h"

#include "../Util/STD_Util.h"

World::World(const WorldSettings& worldSettings, const Camera& camera)
:   m_worldSettings (worldSettings)
,   m_pCamera       (&camera)
{

}

const WorldSettings& World::getWorldSettings() const
{
    return m_worldSettings;
}


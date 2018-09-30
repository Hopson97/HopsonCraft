#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/MasterRenderer.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "../Maths/PositionConversion.h"

#include "../Util/STD_Util.h"

World::World(const Camera& camera)
:   m_pCamera       (&camera)
{

}

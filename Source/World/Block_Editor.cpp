#include "Block_Editor.h"

#include <SFML/Window/Mouse.hpp>

#include "Chunk/CMap.h"

#include "../Maths/General_Maths.h"
#include "../Physics/Ray.h"
#include "../Player.h"

Block_Editor::Block_Editor(Chunk::Map& chunkMap)
:   m_p_chunkMap    (&chunkMap)
{ }

void Block_Editor::input(Player& player)
{
    Ray raycast (player.rotation.y + 90,
                 player.rotation.x,
                 player.position);

    for (uint32_t i = 0; i < 4 / 0.1; i++)
    {
        raycast.step(0.1);

        if(isHitBlock(raycast))
        {
            if (editBlock(raycast))
                break;
        }
    }
}

bool Block_Editor::isHitBlock(const Ray& ray) const
{
    CBlock block = m_p_chunkMap->getBlockAt(ray.getEndPoint());
    return !(block == Block::ID::Air);
}

bool Block_Editor::editBlock(const Ray& ray)
{
    if(m_editorTimer.getElapsedTime().asSeconds() > 0.1 &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_editorTimer.restart();
        m_p_chunkMap->breakBlock(ray.getEndPoint());
        return true;
    }
    else
    {
        return false;
    }
}


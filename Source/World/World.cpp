#include "World.h"

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <iostream>

#include "../World/World.h"
#include "../World/Block/D_Blocks.h"
#include "../World/Block/Block_Type/Block_Type.h"
#include "../World/Block/Block_Enums.h"

#include "../Util/Debug_Display.h"
#include "../Util/Display.h"
#include "../Util/Time.h"

#include "../Maths/Position_Converter_Maths.h"
#include "../Maths/General_Maths.h"
#include "../Maths/Ray.h"

#include "../Renderer/Master_Renderer.h"
#include "../Input/Key_Binds.h"

World::World(uint32_t seed,
             const std::string& name)
:   m_name              (name)
,   m_player            (m_chunkMap)
,   m_chunkMap          (m_player.getChunkLocation(), name, seed, *this)
,   m_seed              (seed)
{
    loadWorldFile();
}

void World::input(const sf::Event& e)
{
    m_player.input(e);
}

void World::input()
{
    blockRayHit();
}

void World::update(float dt, Camera& camera)
{
    m_player.input(camera);
    m_player.update(dt);

    m_chunkMap.checkChunks();//This must be the last thing to happen in the update function here!
}

void World::draw(float dt, Master_Renderer& renderer)
{
    m_chunkMap.draw(renderer);
}

void World::drawXHair(Master_Renderer& renderer)
{
    m_crosshair.draw(renderer);
}


void World::blockRayHit()
{
    static sf::Clock blockEditTimer;
    auto& rotation    = m_player.rotation;
    auto& position    = m_player.position;

    auto lastRayPos  = m_player.position;


    Maths::Ray ray(rotation.y + 90,
                   rotation.x,
                   position);

    for (int s = 0 ; s < 6 / 0.1 ; s++)
    {
        ray.step(0.1);
        auto* block = &m_chunkMap.getBlockAt(ray.getEndPoint());

        if (block->getData().getPhysicalState() == Block::Physical_State::Solid ||
            block->getData().getPhysicalState() == Block::Physical_State::Flora)
        {
            m_crosshair.showMiningTexture();
            if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)        ||
                 sf::Mouse::isButtonPressed(sf::Mouse::Right))      &&
                 blockEditTimer.getElapsedTime().asSeconds() > 0.2)
            {
                blockEdit(lastRayPos, ray.getEndPoint());
                blockEditTimer.restart();
            }
            break;
        }
        else
        {
            m_crosshair.showRegularTexture();
        }
        lastRayPos = ray.getEndPoint();
    }
}

void World::blockEdit(const Vector3& lastRayPos, const Vector3& rayPos)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_chunkMap.addBlock(Block::get(Block::ID::Air), rayPos);
        m_chunkMap.makeExplosion(rayPos, 8);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        Chunk* chunk = m_chunkMap.getChunkAt(Maths::worldToChunkPosition(rayPos));
        auto interaction = chunk->getBlocks().getBlock(Maths::worldToBlockPosition(rayPos)).interact(*chunk, Maths::worldToBlockPosition(rayPos), Empty());

        switch (interaction)
        {
            case Block::Interaction_Type::Chunk_Block_Change:
                m_chunkMap.addChangedChunk(chunk);
                break;

            case Block::Interaction_Type::None:
                m_chunkMap.addBlock(m_player.getBlock(), lastRayPos);
                break;
        }
    }
}
//Saving a loading...
void World::loadWorldFile()
{
    std::ifstream inFile("Worlds/" + m_name + "/World_Info.data");
    std::string line;
    if (std::getline(inFile, line))
    {
        if (line == "pos")
        {
            int x, y, z;
            inFile >> x >> y >> z;
            m_player.setPosition({x + 0.5,
                                  y,            //Offset by 0.5 as the exact numbers put the player on a block corner
                                  z + 0.5});
        }
    }
}

void World::save() const
{
    m_chunkMap.saveChunks();

    auto& position = m_player.position;

    std::ofstream outFile ("Worlds/" + m_name + "/World_Info.data");
    std::cout << "Worlds/" << m_name << "/World_Info.data" << std::endl;
    outFile << "pos\n"  << (int)position.x << " " << (int)position.y << " " << (int)position.z << std::endl;

    outFile << "seed\n" << m_seed                   << std::endl;
    outFile << "time\n" << Time::getTimeString()    << std::endl;
    outFile << "date\n" << Time::getDateString()    << std::endl;
}


//Getters...
const Chunk_Map& World::getChunkMap() const
{
    return m_chunkMap;
}

const Player& World::getPlayer() const
{
    return m_player;
}



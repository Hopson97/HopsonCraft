#include "CColumn.h"

#include <SFML/System/Clock.hpp>
#include <cmath>

#include "../../Renderer/RMaster.h"
#include "../../Util/Random.h"

namespace Chunk
{
    Column::Column(const Position& pos, Map& map)
    :   m_position      (pos)
    ,   m_p_chunkMap    (&map)
    {
        sf::Clock clock;

        for (int i = 0; i < Random::intInRange(6, 8); i++)
        {
            addChunklet();
        }

        for (int32_t y = 0; y < m_chunkCount * World_Constants::CH_SIZE; y++)
        {
            for (int32_t x = 0; x < World_Constants::CH_SIZE; x++)
            {
                for (int32_t z = 0; z < World_Constants::CH_SIZE; z++)
                {
                    y == m_chunkCount * World_Constants::CH_SIZE - 1 ?
                        setBlock({x, y, z}, Block::ID::Grass)    :
                        setBlock({x, y, z}, Block::ID::Dirt);
                }
            }
        }
    }

    void Column::createFullMesh()
    {
        for (auto& c : m_chunklets)
        {
            c->createMesh();
        }
        m_flags.hasFullMesh = true;
    }


    void Column::setBlock(const Block::Column_Position& pos, CBlock block)
    {
        auto chunklet = std::ceil(pos.y / World_Constants::CH_SIZE);

        int8_t yPos = pos.y - World_Constants::CH_SIZE * chunklet;

        m_chunklets.at(chunklet)->qSetBlock({ (int8_t)pos.x,
                                                      yPos,
                                              (int8_t)pos.z}, block);
    }

    const Chunklet* Column::getChunklet(int32_t index) const
    {
        if (index > m_chunkCount - 1)
        {
            return nullptr;
        }
        else if (index < 0)
        {
            return nullptr;
        }
        return m_chunklets.at(index).get();
    }


    const Position& Column::getPosition () const
    {
        return m_position;
    }

    const Column::CFlags& Column::getFlags ()
    {
        return m_flags;
    }

    void Column::setDeleteFlag (bool deleteF)
    {
        m_flags.deleteMe = deleteF;
    }

    void Column::draw(Renderer::Master& renderer)
    {
        for(auto itr = m_chunklets.begin(); itr != m_chunklets.end();)
        {
            Chunklet& chunklet = *(*itr);
            if (chunklet.getFlags().hasFaces)
            {
                if (chunklet.getFlags().hasBuffered)
                {
                    ++itr;
                    renderer.draw(chunklet);
                }
                else
                {
                    chunklet.bufferMesh();
                }
            }
            else
            {
                itr++;
            }
        }
    }

    void Column::addChunklet()
    {
        m_chunklets.push_back(std::make_unique<Chunklet>
                              (Chunklet_Position(m_position.x,
                                                 m_chunkCount++,
                                                 m_position.y),
                               *m_p_chunkMap));
    }


}

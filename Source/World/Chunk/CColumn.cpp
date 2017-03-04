#include "CColumn.h"

#include "../../Renderer/RMaster.h"

namespace Chunk
{
    Column::Column(const Position& pos, Map& map)
    :   m_position      (pos)
    ,   m_p_chunkMap    (&map)
    {
        m_chunklets.push_back(std::make_unique<Chunklet>
                              (Chunklet_Position{0, m_chunkCount, 0},
                               *m_p_chunkMap));

        m_chunklets.at(0)->createMesh();
    }

    const Position& Column::getPosition() const
    {
        return m_position;
    }


    void Column::draw(Renderer::Master& renderer)
    {
        for(auto& c : m_chunklets)
        {
            renderer.draw(*c);
        }
    }

}

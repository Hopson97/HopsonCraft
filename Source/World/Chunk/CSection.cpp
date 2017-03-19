#include "CSection.h"

#include "../World_Constants.h"

namespace Chunk
{
    Section::Section(const Chunklet_Position& position)
    :   m_position      (position)
    ,   m_meshBuilder   (*this)
    {
        m_meshBuilder.generateMesh(m_meshes);
        m_meshes.solidMesh.buffer();
    }

    Section* Section::getSection(const Block::Small_Position& position)
    {
        static const sf::Vector3<int32_t> noChnage(0, 0, 0);
        auto change = noChnage;

        auto pos = position;

        checkBound(pos.x, change.x);
        checkBound(pos.y, change.y);
        checkBound(pos.z, change.z);

        if (change == noChnage)
        {
            return this;
        }
        else
        {
            //@TODO Change to return actual chunk
            return nullptr;
        }

    }

    const Section* Section::getConstSection(const Block::Small_Position& position) const
    {
        static const sf::Vector3<int32_t> noChnage(0, 0, 0);
        auto change = noChnage;

        auto pos = position;

        checkBound(pos.x, change.x);
        checkBound(pos.y, change.y);
        checkBound(pos.z, change.z);

        if (change == noChnage)
        {
            return this;
        }
        else
        {
            //@TODO Change to return actual chunk
            return nullptr;
        }

    }

    void Section::checkBound(int8_t& dir, int32_t& change) const
    {
        if (dir > CHUNK_SIZE - 1)
        {
            change = -1;
        }
        else if (dir < 0)
        {
            change = 1;
        }
    }



    uint32_t Section::getIndexFrom(const Block::Small_Position& position) const
    {
        return position.y *
               CHUNK_AREA + position.z *
               CHUNK_SIZE + position.x;
    }

}

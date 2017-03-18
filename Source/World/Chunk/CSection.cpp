#include "CSection.h"

#include "../World_Constants.h"

namespace Chunk
{
    Section::Section(const Chunklet_Position& position)
    :   m_position  (position)
    { }

    void Section::setBlock(const Block::Small_Position& position, CBlock block)
    {
        m_blocks[getIndexFrom(position)] = block;
    }

    CBlock Section::getBlock(const Block::Small_Position& position)
    {
        return m_blocks[getIndexFrom(position)];
    }

    Section* Section::getSection(const Block::Small_Position& position)
    {
        static const sf::Vector3<int32_t> noChnage(0, 0, 0);
        auto change = noChnage;

        checkBound(position.x, change.x);
        checkBound(position.y, change.y);
        checkBound(position.z, change.z);

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

    void Section::checkBound(int8_t dir, int32_t& change)
    {
        if (dir > Constants::CHUNK_SIZE - 1)
            change = -1;

        else if (dir < 0)
            change = 1;
    }



    uint32_t Section::getIndexFrom(const Block::Small_Position& position)
    {
        return position.y *
               Constants::CHUNK_AREA + position.z *
               Constants::CHUNK_SIZE + position.x;
    }

}

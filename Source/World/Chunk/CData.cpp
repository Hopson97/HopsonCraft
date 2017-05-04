#include "CData.h"

namespace Chunk
{
    /*
    //Blocks
    void Data::setBlock(Block::Small_Position& position, CBlock block)
    {
        const auto& section = getSection(position, this, *mp_chunks);
        if(section)
        {
            section->qSetBlock(position, block);
            section->getParentChunk().updateTopBlockLocation({position.x,
                                                              position.y * m_position.y,
                                                              position.z});
        }
    }

    CBlock Data::getBlock(Block::Small_Position& position) const
    {
        const auto&  section = getConstSection(position, this, *mp_chunks);
        return  section ?
                section->qGetBlock(position) :
                Block::ID::Air;
    }



    //Natural Light
    void Data::setNaturalLight(Block::Small_Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *mp_chunks);
        if(section)
        {
            section->qSetNaturalLight(position, value);
        }
    }

    uint8_t Data::getNaturalLight(Block::Small_Position& position) const
    {
        const auto& section = getConstSection(position, this, *mp_chunks);

        return  section ?
                section->qGetNaturalLight(position) :
                MAX_LIGHT;
    }


    //Block lights
    void Data::setBlockLight(Block::Small_Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *mp_chunks);
        if(section)
        {
            section->qSetBlockLight(position, value);
        }
    }

    uint8_t Data::getBlockLight(Block::Small_Position& position) const
    {
        const auto& section = getConstSection(position, this, *mp_chunks);
        if(section)
        {
            return section->qGetBlockLight(position);
        }
        else
        {
            return MAX_LIGHT;
        }
    }

    void Data::qSetBlock(const Block::Small_Position& position, CBlock block)
    {
        m_layerHasAir[position.y].update(block);
        m_blocks.at(position) = block;
    }

    CBlock Data::qGetBlock(const Block::Small_Position& position) const
    {
        return m_blocks.at(position);
    }

    void Data::qSetBlockLight(const Block::Small_Position& position, uint8_t value)
    {
        m_light.at(position).block = value;
    }

    uint8_t Data::qGetBlockLight(const Block::Small_Position& position) const
    {
        return m_light.at(position).block;
    }

    void Data::qSetNaturalLight(const Block::Small_Position& position, uint8_t value)
    {
        m_light.at(position).natural = value;
    }

    uint8_t Data::qGetNaturalLight(const Block::Small_Position& position) const
    {
        return m_light.at(position).natural;
    }
    */
}

#include "CSection.h"

namespace Chunk
{
    //===============================
    //Blocks
    void Section::setBlock(const Block::Small_Position& position, CBlock block)
    {
        Section* section = getSection(position);
        if(section)
        {
            section->qSetBlock(position, block);
        }
    }

    CBlock Section::getBlock(const Block::Small_Position& position) const
    {
        auto* section = getConstSection(position);
        if(section)
        {
            return section->qGetBlock(position);
        }
        else
        {
            return Block::ID::Air;
        }
    }

    //===============================
    //Natural Light
    void Section::setNaturalLight(const Block::Small_Position& position, uint8_t value)
    {
        Section* section = getSection(position);
        if(section)
        {
            section->qSetNaturalLight(position, value);
        }
    }

    uint8_t Section::getNaturalLight(const Block::Small_Position& position) const
    {
        auto* section = getConstSection(position);
        if(section)
        {
            return section->qGetNaturalLight(position);
        }
        else
        {
            return MAX_LIGHT;
        }
    }

    //===============================
    //Block lights
    void Section::setBlockLight(const Block::Small_Position& position, uint8_t value)
    {
        Section* section = getSection(position);
        if(section)
        {
            section->qSetBlockLight(position, value);
        }
    }

    uint8_t Section::getBlockLight(const Block::Small_Position& position) const
    {
        auto* section = getConstSection(position);
        if(section)
        {
            return section->qGetBlockLight(position);
        }
        else
        {
            return MAX_LIGHT;
        }
    }

    void Section::qSetBlock(const Block::Small_Position& position, CBlock block)
    {
        m_layerHasAir[position.y].update(block);
        m_blocks[getIndexFrom(position)] = block;
    }

    CBlock Section::qGetBlock(const Block::Small_Position& position) const
    {
        return m_blocks[getIndexFrom(position)];
    }

    void Section::qSetBlockLight(const Block::Small_Position& position, uint8_t value)
    {
        m_light[getIndexFrom(position)].block = value;
    }

    uint8_t Section::qGetBlockLight(const Block::Small_Position& position) const
    {
        return m_light[getIndexFrom(position)].block;
    }

    void Section::qSetNaturalLight(const Block::Small_Position& position, uint8_t value)
    {
        m_light[getIndexFrom(position)].natural = value;
    }

    uint8_t Section::qGetNaturalLight(const Block::Small_Position& position) const
    {
        return m_light[getIndexFrom(position)].natural;
    }
}

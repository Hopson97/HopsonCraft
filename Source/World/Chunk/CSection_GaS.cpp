#include "CSection.h"

#include "CBoundsCheck.h"
#include "CFull_Chunk.h"
#include "../World_Constants.h"
#include "CMap.h"

namespace Chunk
{
    //===============================
    //Blocks
    void Section::setBlock(Block::Small_Position& position, CBlock block)
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

    CBlock Section::getBlock(Block::Small_Position& position) const
    {
        const auto&  section = getConstSection(position, this, *mp_chunks);
        return  section ?
                section->qGetBlock(position) :
                Block::ID::Air;
    }


    //===============================
    //Natural Light
    void Section::setNaturalLight(Block::Small_Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *mp_chunks);
        if(section)
        {
            section->qSetNaturalLight(position, value);
        }
    }

    uint8_t Section::getNaturalLight(Block::Small_Position& position) const
    {
        const auto& section = getConstSection(position, this, *mp_chunks);

        return  section ?
                section->qGetNaturalLight(position) :
                MAX_LIGHT;
    }

    //===============================
    //Block lights
    void Section::setBlockLight(Block::Small_Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *mp_chunks);
        if(section)
        {
            section->qSetBlockLight(position, value);
        }
    }

    uint8_t Section::getBlockLight(Block::Small_Position& position) const
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






    void Section::qSetBlock(const Block::Small_Position& position, CBlock block)
    {
        m_layerHasAir[position.y].update(block);
        m_blocks.at(position) = block;
    }

    CBlock Section::qGetBlock(const Block::Small_Position& position) const
    {
        return m_blocks.at(position);
    }

    void Section::qSetBlockLight(const Block::Small_Position& position, uint8_t value)
    {
        m_light.at(position).block = value;
    }

    uint8_t Section::qGetBlockLight(const Block::Small_Position& position) const
    {
        return m_light.at(position).block;
    }

    void Section::qSetNaturalLight(const Block::Small_Position& position, uint8_t value)
    {
        m_light.at(position).natural = value;
    }

    uint8_t Section::qGetNaturalLight(const Block::Small_Position& position) const
    {
        return m_light.at(position).natural;
    }



    //Layers
    const Section::Layer& Section::getLayer(int8_t y)const
    {
        ///@TODO This to use better bounds
        if (y == -1)
        {
            const auto& chunk = mp_chunks->get({m_position.x, m_position.y - 1, m_position.z});
            if(!chunk)
            {
                return errorLayer;
            }
            else return chunk->m_layerHasAir[CHUNK_SIZE - 1];
        }
        else if (y == CHUNK_SIZE)
        {
            const Section* chunk = mp_chunks->get({m_position.x, m_position.y + 1, m_position.z});
            if(!chunk)
            {
                return errorLayer;
            }
            else return chunk->m_layerHasAir[0];
        }
        else
        {
            return m_layerHasAir[y];
        }
    }


    const Section* Section::getAdjacentSection(const Vector2& change) const
    {
        return mp_chunks->get({ m_position.x + (int32_t)change.x,
                                m_position.y,
                                m_position.z + (int32_t)change.y});
    }

}

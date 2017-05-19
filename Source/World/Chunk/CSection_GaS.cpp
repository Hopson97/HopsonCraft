#include "CSection.h"

#include "CBoundsCheck.h"
#include "CFull_Chunk.h"
#include "../World_Constants.h"
#include "CMap.h"

namespace Chunk
{

    //Getters/ Setters with bounds checks
    void Section::setBlock(Block::Small_Position& position, CBlock block, bool generatedBlock)
    {
        const auto& section = getSection(position, this, *m_pChunkMap);
        if(section)
        {
            section->qSetBlock(position, block, generatedBlock);
            section->getParentChunk().updateTopBlockLocation({position.x,
                                                              position.y * m_position.y,
                                                              position.z});
        }
    }

    CBlock Section::getBlock(Block::Small_Position& position) const
    {
        const auto&  section = getConstSection(position, this, *m_pChunkMap);
        return  section ?
                section->qGetBlock(position) :
                Block::ID::Air;
    }

    void Section::setNaturalLight(Block::Small_Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *m_pChunkMap);
        if(section)
        {
            section->qSetNaturalLight(position, value);
        }
    }

    uint8_t Section::getNaturalLight(Block::Small_Position& position) const
    {
        const auto& section = getConstSection(position, this, *m_pChunkMap);

        return  section ?
                section->qGetNaturalLight(position) :
                MAX_LIGHT;
    }

    void Section::setBlockLight(Block::Small_Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *m_pChunkMap);
        if(section)
        {
            section->qSetBlockLight(position, value);
        }
    }

    uint8_t Section::getBlockLight(Block::Small_Position& position) const
    {
        const auto& section = getConstSection(position, this, *m_pChunkMap);
        return  section ?
                section->qGetBlockLight(position) :
                MAX_LIGHT;
    }

    //Quick functions
    void Section::qSetBlock(const Block::Small_Position& position, CBlock block, bool generatedBlock)
    {
        if (block.getData().canUpdate)
        {
            m_hasUpdatableBlocks = true;
        }
        if (m_parentChunk->hasGeneratedBlockData && !generatedBlock)
        {
            m_placedBlocks.emplace_back(block, (uint16_t)m_blocks.getIndex(position));
        }

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
            const auto& chunk = m_pChunkMap->get({m_position.x, m_position.y - 1, m_position.z});
            if(!chunk)
            {
                return errorLayer;
            }
            else return chunk->m_layerHasAir[CHUNK_SIZE - 1];
        }
        else if (y == CHUNK_SIZE)
        {
            const Section* chunk = m_pChunkMap->get({m_position.x, m_position.y + 1, m_position.z});
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
        return m_pChunkMap->get({ m_position.x + (int32_t)change.x,
                                m_position.y,
                                m_position.z + (int32_t)change.y});
    }

}

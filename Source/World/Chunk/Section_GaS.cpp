#include "Section.h"

#include "BoundsCheck.h"
#include "Full_Chunk.h"
#include "Map.h"
#include "../World_Constants.h"

namespace Chunk
{

    //Getters/ Setters with bounds checks
    void Section::setBlock(Block::Position& position, CBlock block, bool generatedBlock)
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

    CBlock Section::getBlock(Block::Position& position) const
    {
        const auto&  section = getConstSection(position, this, *m_pChunkMap);
        return  section ?
                section->qGetBlock(position) :
                Block::ID::Air;
    }

    void Section::setNaturalLight(Block::Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *m_pChunkMap);
        if(section)
        {
            section->qSetNaturalLight(position, value);
        }
    }

    uint8_t Section::getNaturalLight(Block::Position& position) const
    {
        const auto& section = getConstSection(position, this, *m_pChunkMap);

        return  section ?
                section->qGetNaturalLight(position) :
                MAX_LIGHT;
    }

    void Section::setBlockLight(Block::Position& position, uint8_t value)
    {
        const auto& section = getSection(position, this, *m_pChunkMap);
        if(section)
        {
            section->qSetBlockLight(position, value);
        }
    }

    uint8_t Section::getBlockLight(Block::Position& position) const
    {
        const auto& section = getConstSection(position, this, *m_pChunkMap);
        return  section ?
                section->qGetBlockLight(position) :
                MAX_LIGHT;
    }

    //Quick functions
    void Section::qSetBlock(const Block::Position& position, CBlock block, bool generatedBlock)
    {
        /*
        if (m_parentChunk->hasGeneratedBlockData && !generatedBlock)
        {
            m_placedBlocks.emplace_back(block, (uint16_t)m_blocks.getIndex(position));
        }*/

        m_layerHasAir[position.y].update(block);
        m_blocks.at(position) = block;
    }

    CBlock Section::qGetBlock(const Block::Position& position) const
    {
        return m_blocks.at(position);
    }

    void Section::qSetBlockLight(const Block::Position& position, uint8_t value)
    {
        m_light.at(position).block = value;
    }

    uint8_t Section::qGetBlockLight(const Block::Position& position) const
    {
        return m_light.at(position).block;
    }

    void Section::qSetNaturalLight(const Block::Position& position, uint8_t value)
    {
        m_light.at(position).natural = value;
    }

    uint8_t Section::qGetNaturalLight(const Block::Position& position) const
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
        return m_pChunkMap->get({   m_position.x + static_cast<int>(change.x),
                                    m_position.y,
                                    m_position.z + static_cast<int>(change.y)});
    }

}

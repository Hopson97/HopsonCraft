#include "CFull_Chunk.h"

#include <iostream>

#include "../World_Constants.h"
#include "../../Maths/General_Maths.h"
#include "../../Maths/Position_Conversion.h"
#include "../../Camera.h"
#include "../../Renderer/RMaster.h"
#include "../../Util/Random.h"
#include "../../Util/Hasher.h"

#include "../World_Settings.h"

#include "../../Temp/Noise_Generator.h"

#include "../Generators/GStructures.h"

namespace Chunk
{
    Full_Chunk::Full_Chunk(World& world,
                           Map& map,
                           const Position& position,
                           const World_Settings& settings)
    :   mp_world    {&world}
    ,   mp_chunkMap {&map}
    ,   m_position  {position}
    { }


    void Full_Chunk::tick()
    {
        for (auto& chunk : m_chunkSections)
        {
            chunk->tick(*mp_world);
        }
    }


    void Full_Chunk::setBlock(const Block::Position& position,
                               CBlock block,
                               bool overrideBlocks)
    {
        addSections(position.y);

        auto pos = Maths::blockToSmallBlockPos(position);

        m_chunkSections[position.y / CHUNK_SIZE]
            ->setBlock(pos, block);
    }

    void Full_Chunk::qSetBlock(const Block::Position& position,
                               CBlock block,
                               bool overrideBlocks)
    {
        addSections(position.y);
        updateTopBlockLocation(position);

        m_chunkSections.at(position.y / CHUNK_SIZE)
            ->qSetBlock(Maths::blockToSmallBlockPos(position), block);
    }

    CBlock Full_Chunk::getBlock(const Block::Position& position)
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;
        if (yPositionSection > (int32_t)m_chunkSections.size() - 1)
        {
            return Block::ID::Air;
        }
        else
        {
            auto pos = Maths::blockToSmallBlockPos(position);

            return m_chunkSections[yPositionSection]
                ->getBlock(pos);
        }
    }

    CBlock Full_Chunk::qGetBlock(const Block::Position& position)
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;
        if (yPositionSection > (int32_t)m_chunkSections.size() - 1)
        {
            return Block::ID::Air;
        }
        else
        {
            return m_chunkSections[yPositionSection]
                ->qGetBlock(Maths::blockToSmallBlockPos(position));
        }
    }

    void Full_Chunk::updateTopBlockLocation(const Block::Position& position)
    {
        auto val = m_highestBlocks.at(position.x, position.z);
        if ((int32_t)val < position.y)
        {
            m_highestBlocks.at(position.x, position.z) = position.y;
        }
    }

    void Full_Chunk::addSections(uint32_t blockTarget)
    {
        int32_t yPositionSection = blockTarget / CHUNK_SIZE;

        while (yPositionSection > m_sectionCount - 1)
        {
            addSection();
        }
    }

    ///@TODO Fix and test this function
/*
    bool Full_Chunk::overrideBlockFails(bool overrideBlocks, const Block::Position& position)
    {
        if (!overrideBlocks)
        {
            return qGetBlock(position).getData().blockID != Block::ID::Air;
        }
    }
*/

    const Position& Full_Chunk::getPosition() const
    {
        return m_position;
    }

    Section* Full_Chunk::getSection(int32_t index, bool)
    {
        //This causes trees and other structures to sometimes not work correctly!
        if (index < 0 || index > m_sectionCount) return nullptr;

        while (index > m_sectionCount - 1)
        {
            addSection();
        }

        return m_chunkSections[index].get();
    }


    void Full_Chunk::addSection()
    {
        Chunklet_Position position (m_position.x, m_sectionCount++, m_position.y);

        m_chunkSections.push_back(std::make_unique<Section>(position,
                                                            *mp_chunkMap,
                                                            *this));
    }

    //Adds all of the chunks within the viewing frustum into the master renderer
    //Returns number of faces drawn
    uint32_t Full_Chunk::draw(Renderer::Master& renderer, const Camera& camera)
    {
        int facesDrawn = 0;
        for (auto& chunk : m_chunkSections)
        {
            //No point trying to render a chunk with no faces
            if (chunk->getMeshes().hasFaces())
            {
                //Frustum test
                if(!camera.getFrustum().boxInFrustum(chunk->getAABB()))
                {
                    continue;
                }

                if (chunk->made)
                {
                    if (chunk->buffered)
                    {
                        renderer.draw(*chunk);
                        facesDrawn += chunk->getMeshes().getFacesCount();

                    }
                    else
                    {
                        chunk->bufferMesh();
                    }
                }
            }
        }
        return facesDrawn;
    }

/**/
    bool Full_Chunk::tryGen()
    {
        for (auto& chunk : m_chunkSections)
        {
            if (!chunk->made)
            {
                chunk->makeMesh();
                return true;
            }
        }
        return false;
    }
/**/
/*
    Chunk::Section* Full_Chunk::tryGen()
    {
        for (auto& chunk : m_chunkSections)
        {
            if (!chunk->made)
            {
                return chunk.get();
            }
        }
        return nullptr;
    }
/**/

    uint32_t Full_Chunk::getHeightAt(int8_t x, int8_t z) const
    {
        return m_highestBlocks.at(x, z);
    }
}

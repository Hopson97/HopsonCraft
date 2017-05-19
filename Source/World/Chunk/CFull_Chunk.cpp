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
    :   m_position  {position}
    ,   m_pWorld    {&world}
    ,   m_pChunkMap {&map}
    { }


    void Full_Chunk::tick()
    {
        for (auto& chunk : m_chunkSections)
        {
            chunk->tick(*m_pWorld);
        }
    }


    void Full_Chunk::setBlock(const Block::Position& position,
                               CBlock block,
                               bool overrideBlocks)
    {
        addSections(position.y);

        auto pos = Maths::blockToSmallBlockPos(position);

        getSection(position.y / CHUNK_SIZE)
            ->setBlock(pos, block);
    }

    void Full_Chunk::qSetBlock(const Block::Position& position,
                               CBlock block,
                               bool overrideBlocks)
    {
        addSections(position.y);
        updateTopBlockLocation(position);

        getSection(position.y / CHUNK_SIZE)
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

            getSection(yPositionSection)
                ->getBlock(pos);
        }
        return Block::ID::Air;
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
            return getSection(yPositionSection)
                ->qGetBlock(Maths::blockToSmallBlockPos(position));
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
        Chunklet_Position position (m_position.x,
                                    m_sectionCount++,
                                    m_position.y);

        m_chunkSections.push_back(std::make_unique<Section>(position,
                                                            *m_pChunkMap,
                                                            *this));
        m_maxBlockHeight += CHUNK_SIZE - 1;
    }

    void Full_Chunk::updateTopBlockLocation(const Block::Position& position)
    {
        int val = m_highestBlocks.at(position.x, position.z);

        m_highestBlocks.at(position.x, position.z) = std::max((int)val, position.y);
    }


    //Adds all of the chunks within the viewing frustum into the master renderer
    //Returns number of faces drawn
    uint32_t Full_Chunk::draw(Renderer::Master& renderer, const Camera& camera)
    {
        int facesDrawn = 0;
        for (auto& chunk : m_chunkSections)
        {
            //No point trying to render a chunk with no faces
            if (chunk->getMeshes().hasFaces)
            {
                //Frustum test
                if(!camera.getFrustum().boxInFrustum(chunk->getAABB()))
                {
                    continue;
                }

                if (chunk->getStates().made)
                {
                    if (chunk->getStates().buffered)
                    {
                        renderer.draw(*chunk);
                        facesDrawn += chunk->getMeshes().faceCount;
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

    bool Full_Chunk::tryGen(/*const Camera& camera*/)
    {
        for (auto& chunk : m_chunkSections)
        {
            if (!chunk->getStates().made)
            {
                //if (!camera.getFrustum().boxInFrustum(chunk->getAABB())) continue;

                chunk->makeMesh();
                return true;
            }
        }
        return false;
    }

    uint32_t Full_Chunk::getHeightAt(int8_t x, int8_t z) const
    {
        return m_highestBlocks.at(x, z);
    }

    const Position& Full_Chunk::getPosition     () const    { return m_position;        }
    const World&    Full_Chunk::getWorld        () const    { return *m_pWorld;         }
    bool            Full_Chunk::hasDeleteFlag   () const    { return m_hasDeleteFlag;   }
    void            Full_Chunk::setForDelete    ()          { m_hasDeleteFlag = true;   }
}














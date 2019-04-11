#include "Full_Chunk.h"

#include <iostream>

#include "../World_File.h"
#include "../World_Constants.h"
#include "../World.h"
#include "../../Maths/General_Maths.h"
#include "../../Maths/Position_Conversion.h"
#include "../../Camera.h"
#include "../../Renderer/RMaster.h"
#include "../../Util/Random.h"
#include "../../Util/Hasher.h"

#include "../World_Settings.h"

#include "../../Temp/Noise_Generator.h"

#include "../Generators/Structures.h"

namespace Chunk
{
    Full_Chunk::Full_Chunk( World& world,
                            Map& map,
                            const Position& position,
                            const World_Settings& settings,
                            World_File& worldFile)
    :   m_position  {position}
    ,   m_pWorld    {&world}
    ,   m_pChunkMap {&map}
    {
    }


    void Full_Chunk::tick()
    {
            /**
                @TODO Use this x and z position to  update top block of
                column at location according to weather conditions
                (of which is not implemented as of 23/05/2017)
            */

/*
        if (Random::intInRange(1, 16) == 1)
        {
            auto x = (uint8_t)Random::intInRange(0, CHUNK_SIZE - 1);
            auto z = (uint8_t)Random::intInRange(0, CHUNK_SIZE - 1);

            auto height = getHeightAt(x, z);
            auto block = qGetBlock(x, height, z);

            auto worldBlockPosition =
                Maths::Convert::chunkBlockToWorldBlockPosition({x, height, z}, getPosition());

        }
*/
        for (auto& chunk : m_chunkSections)
        {
            chunk.tick(*m_pWorld);
        }
    }


    void Full_Chunk::setBlock(const Block::Position& position,
                               CBlock block)
    {
        addSections(position.y);
        auto blockPos = Maths::Convert::chunkBlockToSectionBlockPosition(position);

        editableGetSection(position.y / CHUNK_SIZE)
            ->setBlock(blockPos, block);
    }

    void Full_Chunk::qSetBlock(const Block::Position& position,
                               CBlock block)
    {
        addSections(position.y);
        updateTopBlockLocation(position);

        auto blockPos = Maths::Convert::chunkBlockToSectionBlockPosition(position);

        editableGetSection(position.y / CHUNK_SIZE)
            ->qSetBlock(blockPos, block);
    }

    CBlock Full_Chunk::getBlock(const Block::Position& position) const
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;
        if (yPositionSection > static_cast<int>(m_chunkSections.size() - 1))
        {
            return Block::ID::Air;
        }
        else
        {
            auto blockPos = Maths::Convert::chunkBlockToSectionBlockPosition(position);

            getSection(yPositionSection)
                ->getBlock(blockPos);
        }
        return Block::ID::Air;
    }

    CBlock Full_Chunk::qGetBlock(const Block::Position& position) const
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;
        if (yPositionSection > static_cast<int>(m_chunkSections.size() - 1))
        {
            return Block::ID::Air;
        }
        else
        {
            auto blockPos = Maths::Convert::chunkBlockToSectionBlockPosition(position);

            return getSection(yPositionSection)
                ->qGetBlock(blockPos);
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

    const Section* Full_Chunk::getSection(int32_t index) const
    {
        //This causes trees and other structures to sometimes not work correctly!
        if (index < 0 || index > m_sectionCount)
            return nullptr;

        return &m_chunkSections[index];
    }

    Section* Full_Chunk::editableGetSection (int32_t index)
    {
        //This causes trees and other structures to sometimes not work correctly!
        if (index < 0)
            return nullptr;

        while (index > m_sectionCount - 1)
        {
            addSection();
        }

        return &m_chunkSections[index];
    }


    void Full_Chunk::addSection()
    {
        Chunklet_Position position (m_position.x,
                                    m_sectionCount++,
                                    m_position.y);

        m_chunkSections.emplace_back(position, *m_pChunkMap, *this);
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
            if (chunk.getMeshes().hasFaces)
            {
                //Frustum test
                if(!camera.getFrustum().boxInFrustum(chunk.getAABB()))
                {
                    continue;
                }

                if (chunk.getStates().made)
                {
                    if (chunk.getStates().buffered)
                    {
                        renderer.draw(chunk);
                        facesDrawn += chunk.getMeshes().faceCount;
                    }
                    else
                    {
                        chunk.bufferMesh();
                        renderer.draw(chunk);
                        facesDrawn += chunk.getMeshes().faceCount;
                    }
                }
            }
        }
        return facesDrawn;
    }

    bool Full_Chunk::tryGen()
    {
        for (auto& chunk : m_chunkSections)
        {
            if (!chunk.getStates().made)
            {
                chunk.makeMesh();
                return true;
            }
        }
        return false;
    }

    uint32_t Full_Chunk::getHeightAt(int8_t x, int8_t z) const
    {
        return m_highestBlocks.at(x, z);
    }

    const Position& Full_Chunk::getPosition () const
    {
        return m_position;
    }

    const World& Full_Chunk::getWorld () const
    {
        return *m_pWorld;
    }
    bool Full_Chunk::hasDeleteFlag () const
    {
        return m_hasDeleteFlag;
    }
    void Full_Chunk::setForDelete ()
    {
        m_hasDeleteFlag = true;
    }

    void Full_Chunk::setBlock (int x, int y, int z, CBlock block)
    {
        setBlock({x, y, z}, block);
    }

    void Full_Chunk::qSetBlock (int x, int y, int z, CBlock block)
    {
        qSetBlock({x, y, z}, block);
    }

    CBlock Full_Chunk::qGetBlock (int x, int y, int z) const
    {
        return    qGetBlock({x, y, z});
    }

    CBlock Full_Chunk::getBlock (int x, int y, int z) const
    {
        return    getBlock({x, y, z});
    }


}





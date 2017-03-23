#include "CFull_Chunk.h"

#include "../World_Constants.h"
#include "../../Maths/General_Maths.h"
#include "../../Camera.h"
#include "../../Renderer/RMaster.h"
#include "../../Util/Random.h"

namespace Chunk
{
    Full_Chunk::Full_Chunk(World& world, Map& map, const Position& position)
    :   mp_world    (&world)
    ,   mp_chunkMap (&map)
    ,   m_position  (position)
    {
        int height = Random::intInRange(5, 25);
        for (int32_t y = 0; y < height; ++y)
        {
            for (int32_t x = 0; x <  CHUNK_SIZE; ++x)
            {
                for (int32_t z = 0; z < CHUNK_SIZE; ++z)
                {
                    setBlock({x, y, z}, 1);
                }
            }
        }
    }

    void Full_Chunk::setBlock(const Block::Position& position, CBlock block)
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;

        while (yPositionSection > m_sectionCount - 1)
        {
            addSection();
        }

        ///@TODO Change to use operator [] and regen mesh?
        m_chunkSections.at(yPositionSection)
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
            ///@TODO Change to use operator []
            return m_chunkSections.at(yPositionSection)
                ->qGetBlock(Maths::blockToSmallBlockPos(position));
        }
    }

    const Position& Full_Chunk::getPosition() const
    {
        return m_position;
    }

    Section* Full_Chunk::getSection(int32_t index)
    {
        if (index > m_sectionCount - 1 || index < 0)
        {
            return nullptr;
        }
        else
        {
            ///@TODO Change to use operator []
            return m_chunkSections.at(index).get();
        }
    }


    void Full_Chunk::addSection()
    {
        Chunklet_Position position (m_position.x, m_sectionCount++, m_position.y);

        m_chunkSections.push_back(std::make_unique<Section>(position, *mp_chunkMap));
    }

    void Full_Chunk::draw(Renderer::Master& renderer, const Camera& camera)
    {
        for (auto& chunk : m_chunkSections)
        {
            if(!camera.getFrustum().boxInFrustum(chunk->getAABB()))
                continue;
            if (chunk->made)
            {
                renderer.draw(*chunk);
            }
        }
    }

    bool Full_Chunk::tryGen(const Camera& camera)
    {
        for (auto& chunk : m_chunkSections)
        {
            if(!camera.getFrustum().boxInFrustum(chunk->getAABB()))
                continue;

            if (!chunk->made)
            {
                chunk->makeMesh();
                return true;
            }
        }
        return false;
    }




}

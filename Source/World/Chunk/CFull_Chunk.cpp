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
                           const World_Settings& settings,
                           bool generate)
    :   mp_world    {&world}
    ,   mp_chunkMap {&map}
    ,   m_position  {position}
    {
        if (generate)
            generateBlocks(settings);
    }


    void Full_Chunk::setBlock(const Block::Position& position,
                               CBlock block,
                               bool overrideBlocks)
    {
        addSections(position.y);
        //if (overrideBlockFails(overrideBlocks, position)) return;

        auto pos = Maths::blockToSmallBlockPos(position);

        m_chunkSections[position.y / CHUNK_SIZE]
            ->setBlock(pos, block);
    }

    void Full_Chunk::qSetBlock(const Block::Position& position,
                               CBlock block,
                               bool overrideBlocks)
    {
        addSections(position.y);
        //if (overrideBlockFails(overrideBlocks, position)) return;
        updateTopBlockLocation(position);

        m_chunkSections[position.y / CHUNK_SIZE]
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

    Section* Full_Chunk::getSection(int32_t index)
    {
        if (index < 0) return nullptr;

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
                        facesDrawn +=
                            chunk->getMeshes().solidMesh.getFaceCount() +
                            chunk->getMeshes().floraMesh.getFaceCount() +
                            chunk->getMeshes().liquidMesh.getFaceCount();

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

    bool Full_Chunk::tryGen(const Camera& camera)
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

/*
    Chunk::Section* Full_Chunk::tryGen(const Camera& camera)
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
*/

    void Full_Chunk::generateBlocks(const World_Settings& settings)
    {
        /*
            Good seeds:
                242553
        */
        Noise::Generator gen;
        gen.setSeed(settings.seed);
        gen.setNoiseFunction(settings.noiseData);

        Random::Generator<std::mt19937> generator;
        generator.setSeed(Hasher::hash((int32_t)settings.seed, m_position.x, m_position.y));

        int32_t maxValue = 0;
        std::vector<Block::Position> treeMap;

        //Create height map from noise
        for (int32_t x = 0 ; x < CHUNK_SIZE; ++x)
        {
            for (int32_t z = 0 ; z < CHUNK_SIZE; ++z)
            {
                int32_t heightHere = gen.getValue(x,
                                                  z,
                                                  m_position.x + 3,
                                                  m_position.y + 3);
                m_highestBlocks.at(x, z) = heightHere;
                maxValue = std::max(maxValue, heightHere);
            }
        }


        maxValue = std::max(maxValue, WATER_LEVEL);

        //Populate the blocks
        for (int32_t y = 0; y < maxValue + 1; ++y)
        {
            for (int32_t x = 0; x < CHUNK_SIZE; ++x)
            {
                for (int32_t z = 0; z < CHUNK_SIZE; ++z)
                {
                    Block::ID blockType = Block::ID::Air;
                    int32_t height = m_highestBlocks.at(x, z);

                    if (y > height)
                    {
                        if (y > WATER_LEVEL)
                        {
                            continue;
                        }
                        else
                        {
                            blockType = Block::ID::Water;
                        }
                    }
                    else if (y == height)
                    {
                        if (y >= WATER_LEVEL)
                        {
                            if (y < BEACH_LEVEL)
                            {
                                blockType = Block::ID::Sand;
                            }
                            else
                            {
                                blockType = Block::ID::Grass;
                                if (generator.intInRange(0, 110) == 5)
                                {
                                    treeMap.emplace_back(x, y, z);
                                }
                            }
                        }
                        else
                        {
                            blockType = generator.intInRange(0, 5) > 1 ? Block::ID::Sand :
                                                                         Block::ID::Dirt;
                        }
                    }
                    else if (Maths::inRange(y, height - 3, height))
                    {
                        blockType = Block::ID::Dirt;
                    }
                    else if (y <= height - 4)
                    {
                        blockType = Block::ID::Stone;
                    }

                    qSetBlock({x, y, z}, blockType);
                }
            }
        }

        //Generate trees af
        for (Block::Position& pos : treeMap)
        {
            makeOakTree(*this, pos, generator);
        }
    }

    uint32_t Full_Chunk::getHeightAt(int8_t x, int8_t z) const
    {
        return m_highestBlocks.at(x, z);
    }
}

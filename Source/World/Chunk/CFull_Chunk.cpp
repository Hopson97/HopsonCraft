#include "CFull_Chunk.h"

#include <iostream>

#include "../World_Constants.h"
#include "../../Maths/General_Maths.h"
#include "../../Camera.h"
#include "../../Renderer/RMaster.h"
#include "../../Util/Random.h"
#include "../../Util/Hasher.h"

#include "../../Temp/Noise_Generator.h"

namespace Chunk
{
    Full_Chunk::Full_Chunk(World& world, Map& map, const Position& position, bool generate)
    :   mp_world    (&world)
    ,   mp_chunkMap (&map)
    ,   m_position  (position)
    {
        if (generate)
            generateBlocks();
    }

    void Full_Chunk::setBlock(const Block::Position& position, CBlock block)
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;

        while (yPositionSection > m_sectionCount - 1)
        {
            addSection();
        }

        auto pos = Maths::blockToSmallBlockPos(position);

        switch (m_state)
        {
            case State::New:
                m_positionedBlocks.emplace_back(position, block);
                break;

            case State::Populating:
            case State::Populated:
                m_chunkSections[yPositionSection]
                    ->setBlock(pos, block);
                    break;
        }


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



    void Full_Chunk::qSetBlock(const Block::Position& position, CBlock block)
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;

        while (yPositionSection > m_sectionCount - 1)
        {
            addSection();
        }

        m_chunkSections[yPositionSection]
            ->qSetBlock(Maths::blockToSmallBlockPos(position), block);
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
        Chunklet_Position position (m_position.x, m_sectionCount++, m_position.y);

        m_chunkSections.push_back(std::make_unique<Section>(position, *mp_chunkMap, *this));
    }

    uint32_t Full_Chunk::draw(Renderer::Master& renderer, const Camera& camera)
    {
        uint32_t faces = 0;
        for (auto& chunk : m_chunkSections)
        {
            //No point trying to render a chunk with no faces
            if (chunk->getMeshes().solidMesh.getFaceCount() > 0)
            {
                //Frustum test
                if(!camera.getFrustum().boxInFrustum(chunk->getAABB()))
                    continue;
                if (chunk->made)
                {
                    renderer.draw(*chunk);
                    faces += chunk->getMeshes().solidMesh.getFaceCount();
                }
            }
        }
        return faces;
    }

    bool Full_Chunk::tryGen(const Camera& camera)
    {
        for (auto& chunk : m_chunkSections)
        {
            //if(!camera.getFrustum().boxInFrustum(chunk->getAABB()))
            //    continue;

            if (!chunk->made)
            {
                chunk->makeMesh();
                return true;
            }
        }
        return false;
    }

    void Full_Chunk::generateBlocks()
    {
        m_state = State::Populating;

        static Noise::Generator gen;
        gen.setSeed(5474);
        Random::Generator<std::mt19937> generator;
        generator.setSeed(Hasher::hash(500, m_position.x, m_position.y));
        gen.setNoiseFunction({8, 60, 0.51, 300});

        int32_t maxValue = 0;
        std::vector<int32_t> heightMap (CHUNK_AREA);

        //Create height map from noise
        for (int32_t x = 0 ; x < CHUNK_SIZE; ++x)
        {
            for (int32_t z = 0 ; z < CHUNK_SIZE; ++z)
            {
                int32_t heightHere = gen.getValue(x, z, m_position.x + 3, m_position.y + 3);
                heightMap[x * CHUNK_SIZE + z] = heightHere;
            }
        }

        maxValue = *std::max_element(heightMap.begin(), heightMap.end());

        //Populate the blocks
        for (int32_t y = 0; y < maxValue + 1; ++y)
        {
            for (int32_t x = 0; x < CHUNK_SIZE; ++x)
            {
                for (int32_t z = 0; z < CHUNK_SIZE; ++z)
                {
                    int32_t height = heightMap[x * CHUNK_SIZE + z];

                    if (y > height) continue;
                    if (y == height)
                    {
                        qSetBlock({x, y, z}, Block::ID::Grass);
                    }
                    else if (y < height && y > height - 4)
                        qSetBlock({x, y, z}, Block::ID::Dirt);
                    else if (y <= height - 4)
                        qSetBlock({x, y, z}, Block::ID::Stone);
                }
            }
        }

        std::cout << "Pos Block:" << m_positionedBlocks.size() << std::endl;
        for (auto& newBlock : m_positionedBlocks)
        {
            setBlock(newBlock.position, newBlock.block);
        }
        m_state = State::Populated;
    }
}







/*
        //Make trees
        for (Block::Position& pos : treeMap)
        {
            auto height = generator.intInRange(5, 8);

            for (int32_t y = 1; y < height; y++)
            {
                qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood);
            }

            int32_t treeSize = 2;
            for (int32_t zLeaf = -treeSize; zLeaf <= treeSize; zLeaf++)
            {
                for (int32_t xLeaf = -treeSize; xLeaf <= treeSize; xLeaf++)
                {
                    setBlock({pos.x + xLeaf, pos.y + height, pos.z + zLeaf},     Block::ID::Oak_Leaf);
                    setBlock({pos.x + xLeaf, pos.y + height + 1, pos.z + zLeaf}, Block::ID::Oak_Leaf);
                    setBlock({pos.x + xLeaf, pos.y + height + 2, pos.z + zLeaf}, Block::ID::Oak_Leaf);
                }
            }
        }
*/

        //Pyramid test
/*
        for (Block::Position& pos : treeMap)
        {
            for(int base = 14, h = 0; base > 0; base -= 2, h++){
                for (int x = pos.x - base / 2; x < pos.x + base / 2; x++){
                    for (int z = pos.z - base / 2; z < pos.z + base / 2; z++){
                        setBlock({pos.x + x, pos.y + h, pos.z + z}, Block::ID::Stone);
                    }
                }
            }
        }
*/

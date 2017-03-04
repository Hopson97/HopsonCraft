#include "CMap.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

#include "../../Renderer/RMaster.h"
#include "Chunklet.h"

namespace Chunk
{
    Map::Map()
    {
        int size = 25;
        for (int z = 0; z < size; z++)
        {
            for (int x = 0; x < size; ++x)
            {
                addChunk({x, z});
            }
        }

        sf::Clock timer;
        for (int z = 0; z < size; z++)
        {
            for (int x = 0; x < size; ++x)
            {
                m_chunks.at({x, z})->createFullMesh();
            }
        }
        auto timed = timer.getElapsedTime().asSeconds();

        std::cout   << "Time to make " << size * size
                    << " chunks: " << timed
                    << " seconds. Average: " << timed / (size * size) << "\n";

    }

    void Map::update()
    {

    }

    void Map::draw(Renderer::Master& renderer)
    {
        for (auto& chunk : m_chunks)
        {
            chunk.second->draw(renderer);// renderer.draw(*chunk.second);
        }
    }

    void Map::addChunk(const Position& pos)
    {
        if(!getChunklet(pos))
        {
            m_chunks.insert(std::make_pair
                           (pos, std::make_unique<Column>(pos, *this)));
        }
    }

    Column* Map::getChunklet(const Chunk::Position& pos)
    {
        if (m_chunks.find(pos) == m_chunks.end())
        {
            return nullptr;
        }
        else
        {
            return m_chunks.at(pos).get();
        }
    }

    const Column* Map::getChunklet(const Chunk::Position& pos) const
    {
        if (m_chunks.find(pos) == m_chunks.end())
        {
            return nullptr;
        }
        else
        {
            return m_chunks.at(pos).get();
        }
    }

}

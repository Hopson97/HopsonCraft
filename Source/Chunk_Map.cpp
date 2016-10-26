#include "Chunk_Map.h"

#include <thread>
#include <iostream>

#include "Maths/Position_Converter_Maths.h"
#include "Camera.h"
#include "Master_Renderer.h"

Chunk_Map::Chunk_Map(const Chunk_Location& playerPosition)
:   m_blockTextures     (1024, 32, "Blocks_Texture_Atlas")
,   m_playerPosition    (&playerPosition)
{
    std::cout << "Chunk map created!" << std::endl;
    std::thread(&Chunk_Map::manageChunks, this).detach();
}

Chunk_Map::~Chunk_Map()
{
    m_isRunning = false;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

Chunk* Chunk_Map::getChunkAt (const Chunk_Location& location)
{
    if (m_chunks.find(location) != m_chunks.end())
    {
        return &*m_chunks.at(location);
    }
    else
    {
        return nullptr;
    }
}

void Chunk_Map::addChunk(const Chunk_Location& location)
{
    if (!getChunkAt(location))
    {
        m_chunks[location] = std::make_unique<Chunk>(location, *this, m_blockTextures);
    }

}

void Chunk_Map::checkChunks()
{
    deleteChunks();
    updateChunks();
}

void Chunk_Map::draw(const Camera& camera, Master_Renderer& renderer)
{
    for (auto itr = m_chunks.begin() ; itr != m_chunks.end() ;)
    {
        Chunk* c = &*(itr)->second;  //So we don't have to dereference the iteraor which looks messy
        if (c->hasBuffered())
        {
            renderer.processChunk(*c);
            itr++;
        }
        else if (c->hasVertexData())
        {
            c->bufferMesh();    //This is only for new chunks, when chunks are updated I just buffer the data there and then
        }
        else
        {
            itr++;
        }
    }
    renderer.render(camera);
}

void Chunk_Map::updateChunks()
{
    for ( auto itr = m_chunksToUpdate.begin() ; itr != m_chunksToUpdate.end() ; )
    {
        (*itr)->generateMesh();
        (*itr)->bufferMesh();
        itr = m_chunksToUpdate.erase( itr );
    }
}

void Chunk_Map::deleteChunks()
{
    for (auto itr = m_chunks.begin() ; itr != m_chunks.end() ;)
    {
        if (itr->second->hasDeleteFlag())
        {
            itr = m_chunks.erase(itr);
        }
        else
        {
            itr++;
        }
    }
}

void Chunk_Map::setBlock (Block::Block_Base& block, const Vector3& worldPosition)
{
    auto addToBatch = [&](int x, int y)
    {
        if (getChunkAt({x, y}))
        {
            m_chunksToUpdate.push_back(getChunkAt({x, y}));
        }
    };

    Chunk_Location position (Maths::worldToChunkPosition(worldPosition));
    Vector3 blockPosition (Maths::worldToBlockPosition(worldPosition));

    Chunk* chunk = getChunkAt(position);

    if (chunk)
    {
        chunk->setBlock(blockPosition, block);
        m_chunksToUpdate.push_back(chunk);
    }
    if (blockPosition.x == 0)
    {
        addToBatch(position.x - 1, position.z);
    }
    if (blockPosition.z == 0)
    {
        addToBatch(position.x, position.z - 1);
    }
    if (blockPosition.x == Chunk::SIZE)
    {
        addToBatch(position.x + 1, position.z);
    }
    if (blockPosition.z == Chunk::SIZE)
    {
        addToBatch(position.x, position.z + 1);
    }
}


struct RenderArea
{
    int minX;
    int minZ;

    int maxX;
    int maxZ;
};


void Chunk_Map :: manageChunks()
{
    while (m_isRunning)
    {
        static RenderArea loadArea;
        static RenderArea deleteArea;

        loadArea.minX =  m_playerPosition->x - m_loadingDistance;
        loadArea.minZ =  m_playerPosition->z - m_loadingDistance;
        loadArea.maxX =  m_playerPosition->x + m_loadingDistance;
        loadArea.maxZ =  m_playerPosition->z + m_loadingDistance;

        generateChunks( loadArea );

        if (m_loadingDistance < m_renderDistance)
        {
            m_loadingDistance++;
        }
        else if  (m_loadingDistance > m_renderDistance)
        {
            m_loadingDistance = m_renderDistance;
        }
        else if (m_loadingDistance == m_renderDistance)
        {
            m_loadingDistance = 2;
        }

        if (!m_isRunning) return;

        deleteArea.minX =  m_playerPosition->x - m_renderDistance;
        deleteArea.minZ =  m_playerPosition->z - m_renderDistance;
        deleteArea.maxX =  m_playerPosition->x + m_renderDistance;
        deleteArea.maxZ =  m_playerPosition->z + m_renderDistance;

        checkChunks( deleteArea );
    }
}

void Chunk_Map :: generateChunks (const RenderArea& area)
{
    std::vector<std::unique_ptr<std::thread>> threads;

    for (int x = area.minX ; x < area.maxX ; x++)
    {
        for (int z = area.minZ ; z < area.maxZ ; z++)
        {
            if (!m_isRunning ) return; //Safety
            if (m_chunks.find( { x, z } ) == m_chunks.end())
            {
                threads.emplace_back(std::make_unique<std::thread>(&Chunk_Map::addChunk, this, Chunk_Location(x, z)));
            }
        }
        for (auto& thread : threads) thread->join();
        threads.clear();
    }
}

void Chunk_Map::checkChunks( const RenderArea& area )
{
    for (auto& chunkPair : m_chunks)
    {
        if (!m_isRunning) return; //Safety

        Chunk& chunk = *chunkPair.second;
        if (chunk.hasDeleteFlag()) continue;

        Chunk_Location loc = chunk.getLocation();
        if (loc.x < area.minX ||
            loc.x > area.maxX ||
            loc.z < area.minZ ||
            loc.z > area.maxZ)
        {
            chunk.setToDelete();
        }
        else
        {
            if (!chunk.hasVertexData() && chunk.hasBlockData())
            {
                chunk.generateMesh();
                if (Maths::getChunkDistance(chunk.getLocation(), *m_playerPosition) < (unsigned)m_renderDistance/ 2)
                {
                    m_loadingDistance = 1;
                }
            }
        }
    }
}

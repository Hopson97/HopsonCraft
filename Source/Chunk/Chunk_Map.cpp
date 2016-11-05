#include "Chunk_Map.h"

#include <iostream>

#include "Maths/Position_Converter_Maths.h"
#include "Maths/General_Maths.h"

#include "Camera.h"
#include "Master_Renderer.h"
#include "Debug_Display.h"
#include "Block/D_Blocks.h"
#include "Function_Toggle_Key.h"

Chunk_Map::Chunk_Map(const Chunk_Location& playerPosition)
:   m_blockTextures     (1024, 16, "Block_Atlas")
,   m_playerPosition    (&playerPosition)
,   m_chunkManageThread (&Chunk_Map::manageChunks, this)
{
    m_chunkManageThread.detach();
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
    static Function_Toggle_Key key([&](){m_renderDistance++;}, sf::Keyboard::Up, 0.5);
    static Function_Toggle_Key ke2y([&](){if(m_renderDistance > 5) m_renderDistance--;}, sf::Keyboard::Down, 0.5);

    key.checkInput  ();
    ke2y.checkInput ();

    deleteChunks();
    updateChunks();
}

void Chunk_Map::draw(Master_Renderer& renderer)
{
    //sf::Clock c;
    m_blockTextures.bind();
    for (auto itr = m_chunks.begin() ; itr != m_chunks.end() ;)
    {
        Chunk* c = &*(itr)->second;  //So we don't have to dereference the iteraor which looks messy
        if (c->hasBuffered())
        {
            //if ((Maths::getChunkDistance(c->getLocation(), *m_playerPosition) <= m_renderDistance))
            {
                renderer.processChunk(*c);
            }
            itr++;
        }
        else if (c->hasMesh())
        {
            c->bufferMesh();    //This is only for new chunks, when chunks are updated I just buffer the data there and then
        }
        else
        {
            itr++;
        }
    }
    //std::cout << c.getElapsedTime().asMicroseconds() << std::endl;
}

void Chunk_Map::updateChunks()
{
    Debug_Display::addChunkUpdates(m_chunksToUpdate.size());
    Debug_Display::addChunkAmounth(m_chunks.size());
    for ( auto itr = m_chunksToUpdate.begin() ; itr != m_chunksToUpdate.end() ; )
    {
        (*itr)->update();
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
    sf::Clock c;
    auto addToBatch = [&](int x, int y)
    {
        auto* c = getChunkAt({x, y});
        if (c)
        {
            if(!c->hasUpdateFlag()){
                c->giveUpdateFlag();
                m_chunksToUpdate.push_back(c);
            }
        }
    };

    Chunk_Location position (Maths::worldToChunkPosition(worldPosition));
    Block_Location blockPosition (Maths::worldToBlockPosition(worldPosition));

    auto* chunk = getChunkAt(position);

    if (chunk)
    {
        chunk->setBlock(blockPosition, block);

        addToBatch(position.x, position.z);

        //Add ajacent blocks to the update batch so that their block faces are updated
        if (blockPosition.x == 0)
            addToBatch(position.x - 1, position.z);

        if (blockPosition.z == 0)
            addToBatch(position.x, position.z - 1);

        if (blockPosition.x == Chunk::SIZE - 1)
            addToBatch(position.x + 1, position.z);

        if (blockPosition.z == Chunk::SIZE - 1)
            addToBatch(position.x, position.z + 1);
    }
}

void Chunk_Map::setBlocks(Block::Block_Base& block, const std::vector<Vector3>worldPositions)
{
    for (auto& position : worldPositions)
    {
        setBlock(block, position);
    }
}


/* isSolidBlockAt

    Used for such things as breaking blocks, as it needs to check if the ray cast in within a solid block.
*/
bool Chunk_Map::isSolidBlockAt(const Vector3& worldPosition)
{
    return getBlockAt(worldPosition).getPhysicalState() == Block::Physical_State::Solid;
}

/* getBlockAt

    Obvious in use.
*/
const Block::Block_Base& Chunk_Map::getBlockAt(const Vector3& worldPosition)
{
    Chunk_Location position (Maths::worldToChunkPosition(worldPosition));
    Block_Location blockPosition (Maths::worldToBlockPosition(worldPosition));

    if (getChunkAt(position))
    {
        return getChunkAt(position)->getBlock(blockPosition);
    }
    return Block::air;
}
/*
makeEplosion:

    Converts Blocks into "air" around point "worldPosition".

    The size of the clearence is dependent on "power"
*/

void Chunk_Map::makeExplosion(const Vector3& worldPosition, int power)
{
    auto& p = worldPosition;

    auto xStart = p.x - power;
    auto yStart = p.y - power;
    auto zStart = p.z - power;

    std::vector<Vector3> positions;
    for (auto y = yStart ; y <= yStart + power * 2 ; y++)
    {
        for (auto x = xStart ; x <= xStart + power * 2 ; x++)
        {
            for (auto z = zStart ; z <= zStart + power * 2 ; z++)
            {
                auto distance = Maths::getDistance({x, y, z}, worldPosition);

                auto factor = power - distance;


                if (factor >= getBlockAt({x,y,z}).getBlastRestistance())
                {
                    positions.emplace_back(x, y, z);
                }

            }
        }
    }
    setBlocks(Block::air, positions);
}


struct Area
{
    Area(int minX, int minZ, int maxX, int maxZ)
    :   minX (minX)
    ,   minZ (minZ)
    ,   maxX (maxX)
    ,   maxZ (maxZ)
    { }

    int minX;
    int minZ;

    int maxX;
    int maxZ;
};


void Chunk_Map :: manageChunks()
{
    while (m_isRunning)
    {
        {
            Area loadArea
            (
                m_playerPosition->x - m_loadingDistance,
                m_playerPosition->z - m_loadingDistance,
                m_playerPosition->x + m_loadingDistance,
                m_playerPosition->z + m_loadingDistance
            );

            generateChunks( loadArea );
            if (!m_isRunning) return;
        }

        {
            Area deleteArea
            (
                m_playerPosition->x - m_renderDistance,
                m_playerPosition->z - m_renderDistance,
                m_playerPosition->x + m_renderDistance,
                m_playerPosition->z + m_renderDistance
            );


            flagChunksForDelete( deleteArea );
            if (!m_isRunning) return;
        }

        {
            Area generationArea
            (
                generationArea.minX =  m_playerPosition->x - m_generationDistance,
                generationArea.minZ =  m_playerPosition->z - m_generationDistance,
                generationArea.maxX =  m_playerPosition->x + m_generationDistance,
                generationArea.maxZ =  m_playerPosition->z + m_generationDistance
            );

            generateMeshes(generationArea);
            if (!m_isRunning) return; //Safety
        }


        if (m_loadingDistance < m_renderDistance)
        {
            m_loadingDistance++;
        }
        else if (m_loadingDistance >= m_renderDistance)
        {
            m_loadingDistance = 2;
        }

        if (m_generationDistance < m_renderDistance)
        {
            m_generationDistance++;
        }
        else if (m_generationDistance >= m_renderDistance)
        {
            m_generationDistance = 2;
        }
    }
}

void Chunk_Map::generateChunks (const Area& createArea)
{
    for (auto x = createArea.minX ; x < createArea.maxX ; x++)
    {
        if (!m_isRunning) return; //Safety
        for (auto z = createArea.minZ ; z < createArea.maxZ ; z++)
        {
            if (!m_isRunning ) return; //Safety
            addChunk({x, z});
        }
    }
}

void Chunk_Map::flagChunksForDelete( const Area& deleteArea )
{
    for (auto& chunkPair : m_chunks)
    {
        if (!m_isRunning) return; //Safety

        Chunk& chunk = *chunkPair.second;
        if (chunk.hasDeleteFlag()) continue;

        Chunk_Location loc = chunk.getLocation();
        if (loc.x < deleteArea.minX ||
            loc.x > deleteArea.maxX ||
            loc.z < deleteArea.minZ ||
            loc.z > deleteArea.maxZ)
        {
            chunk.giveDeleteFlag();
        }
    }
}

void Chunk_Map::generateMeshes(const Area& generationArea)
{
    for (auto x = generationArea.minX ; x < generationArea.maxX ; x++)
    {
        if (!m_isRunning) return; //Safety
        for (auto z = generationArea.minZ ; z < generationArea.maxZ ; z++)
        {
            if (!m_isRunning) return; //Safety
            Chunk* chunk = getChunkAt({x, z});
            if (chunk)
            {
                if (!chunk->hasMesh() && chunk->hasBlockData())
                {
                    chunk->generateMesh();
                }
            }
        }
    }
}

#include "Chunk_Mesh.h"

#include "Chunk.h"
#include "Chunk_Blocks.h"


#include "../../Texture/Texture_Atlas.h"
#include "../Block/Block_Location.h"
#include "../World.h"

namespace
{
    namespace Light_Value
    {
        constexpr float TOP      = 1.0f;
        constexpr float SIDE     = 0.6f;
        constexpr float BOTTOM   = 0.4f;
    }

    const std::vector<GLfloat> ambientOcculsionValues
    {
        0.1f,
        0.4f,
        0.7f,
        1.0f
    };

    const Texture_Atlas* p_atlas = nullptr;
}


void Chunk_Mesh::Chunk_Mesh_Part::addUvCoords (const std::vector<GLfloat>& coords)
{
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
}

void Chunk_Mesh::Chunk_Mesh_Part::addLight(float value)
{
    static float night = 15.0f / 15.0f;
    light.push_back(value * night);
    light.push_back(value * night);
    light.push_back(value * night);
    light.push_back(value * night);
}

void Chunk_Mesh::Chunk_Mesh_Part::buffer()
{
    model.addData   (vertexCoords, textureCoords, indices);
    model.addVBO    (1, light);

    vertexCoords.clear();
    textureCoords.clear();
    light.clear();
    indices.clear();
    indicesCount = 0;

    //Fully clear the vectors
    vertexCoords.shrink_to_fit();
    textureCoords.shrink_to_fit();
    light.shrink_to_fit();
    indices.shrink_to_fit();
}


Chunk_Mesh::Chunk_Mesh(const Chunk& chunk)
:   m_p_chunk (&chunk)
,   m_p_chunkBlocks (&chunk.getBlocks())
{
    if(!p_atlas) p_atlas = &chunk.getAtlas();
}

void Chunk_Mesh::bufferMesh()
{
    m_solidPart.buffer();
    m_waterPart.buffer();
    m_floraPart.buffer();
}

const Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getSolidPart() const
{
    return m_solidPart;
}

const Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getWaterPart() const
{
    return m_waterPart;
}

const Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getFloraPart() const
{
    return m_floraPart;
}


void Chunk_Mesh::generateMesh(int height)
{
    for (int y = 0 ; y < height ; y++)
    {
        if(shouldCreateLayer(y))
        {
            for (int z = 0 ; z < World_Constants::CHUNK_SIZE ; z++)
            {
                for (int x = 0 ; x < World_Constants::CHUNK_SIZE ; x++)
                {
                    if (m_p_chunkBlocks->getBlock({x, y, z}).getData().getPhysicalState() == Block::Physical_State::Gas)
                    {
                        continue;
                    }
                    addBlockMesh (x, y, z, m_p_chunkBlocks->getBlock({x, y, z}).getData());
                }
            }
        }
    }
}

bool Chunk_Mesh::shouldCreateLayer(int y) const
{
    auto adjacentBlockLayerHasAir = [&](int xd, int zd)
    {
        const auto& blocks = m_p_chunk->getAdjBlocks (xd, zd);

        if(blocks)
        {
            return blocks->layerHasTranslucentBlocks (y);
        }
        else
            return true;
    };

    return
                m_p_chunkBlocks->layerHasTranslucentBlocks(y)     ||
                m_p_chunkBlocks->layerHasTranslucentBlocks(y - 1) ||
                m_p_chunkBlocks->layerHasTranslucentBlocks(y + 1) ||
                adjacentBlockLayerHasAir    (1, 0 ) ||
                adjacentBlockLayerHasAir    (0, 1 ) ||
                adjacentBlockLayerHasAir    (-1, 0) ||
                adjacentBlockLayerHasAir    (0, -1);
}


//This is for the block vertex array generator.
//It basically just determines which vertex array, water or ground, to add the verticies into.
Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getPart(const Block::Block_Data& block)
{
    switch(block.getPhysicalState())
    {
        case Block::Physical_State::Solid:
            return m_solidPart;

        case Block::Physical_State::Liquid:
            return m_waterPart;

        case Block::Physical_State::Flora:
            return m_floraPart;

        default:
            break;
    }
    return m_solidPart;
}

//Adds blocks to mesh if there is a adjacent air block to a block
void Chunk_Mesh::addBlockMesh (float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart = &getPart(block);
    m_bh = block.getHeight();

    if (block.getMeshType() == Block::Mesh_Type::X_Style)
    {
        addPlantToMesh(x, y, z, block);
        return;
    }

    if (shouldMakeMesh(x, y + 1, z, block))
    {
        addBlockTopToMesh   (x, y, z, block);
    }
    if (shouldMakeMesh(x, y -1, z, block) && (int)y != 0)
    {
        addBlockBottomToMesh(x, y, z, block);
    }

    if (shouldMakeMesh(x - 1, y, z, block))
    {
        addBlockLeftToMesh  (x, y, z, block);
    }
    if (shouldMakeMesh(x + 1, y, z, block))
    {
        addBlockRightToMesh (x, y, z, block);
    }

    if (shouldMakeMesh(x, y, z + 1, block))
    {
        addBlockFrontToMesh (x, y, z, block);
    }
    if (shouldMakeMesh(x, y, z - 1, block))
    {
        addBlockBackToMesh  (x, y, z, block);
    }
}

bool Chunk_Mesh::shouldMakeMesh(int x, int y, int z, const Block::Block_Data& block)
{
    Block_Location location(x, y, z); //This is so it does not construct this object 3 times, but rather just once.
    auto& b = m_p_chunk->getBlocks().getBlock(location).getData();
    auto id = b.getID();

    return      ( id == Block::ID::Air) ||
                (!b.isOpaque()                                          && id != block.getID()) ||
                ( b.getPhysicalState() == Block::Physical_State::Flora  && id != block.getID()) ||
                (!b.isFullBlock()                                       && id != block.getID());
}


//Some people are confused by this part so here we go:
/*
    So the x, y or z variables refer to the block position, of which is passed into the function.
    The +1 refers to where the vertex is in respect to the block vertex array "origin", of which is the front bottom
    left of a block.
*/

//The top part of a block face, aka the floor
void Chunk_Mesh::addBlockTopToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x,      y + m_bh, z + 1,   //Front-Left
        x + 1,  y + m_bh, z + 1,   //Front-Right
        x + 1,  y + m_bh, z,       //Back-Right
        x,      y + m_bh, z,       //Back-Left
    });


    finishBlockFace(block.getTextureTop(),  Light_Value::TOP);
/*
    finishBlockFace(block.getTextureTop(),  m_p_chunk->getBlocks().getMaxheightAt(x, z) == (int)y ?
                                                Light_Value::TOP :
                                                Light_Value::SIDE);
*/
}

//"Ceiling"
void Chunk_Mesh::addBlockBottomToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x,      y, z,
        x + 1,  y, z,
        x + 1,  y, z + 1,
        x,      y, z + 1,
    });

    finishBlockFace(block.getTextureBottom(), Light_Value::BOTTOM);
}

void Chunk_Mesh::addBlockLeftToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x, y,           z,
        x, y,           z + 1,
        x, y + m_bh,    z + 1,
        x, y + m_bh,    z,
    });

    finishBlockFace(block.getTextureSide(), Light_Value::SIDE);
}

void Chunk_Mesh::addBlockRightToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x + 1, y,           z + 1,
        x + 1, y,           z,
        x + 1, y + m_bh,    z,
        x + 1, y + m_bh,    z + 1,
    });

    finishBlockFace(block.getTextureSide(), Light_Value::SIDE);
}

void Chunk_Mesh::addBlockFrontToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x,      y,          z + 1,
        x + 1,  y,          z + 1,
        x + 1,  y + m_bh,   z + 1,
        x,      y + m_bh,   z + 1,
    });

    finishBlockFace(block.getTextureSide(), Light_Value::SIDE);
}

void Chunk_Mesh::addBlockBackToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x + 1,  y,          z,
        x,      y,          z,
        x,      y + m_bh,   z,
        x + 1,  y + m_bh,   z,
    });

    finishBlockFace(block.getTextureSide(), Light_Value::SIDE);
}

void Chunk_Mesh::finishBlockFace(const Vector2& textureLocation, float lightValue)
{
    m_activePart->addUvCoords(p_atlas->getTextureCoords(textureLocation));
    m_activePart->addLight(lightValue);
    addBlockIndices();
}

//Ambient Occlusion algorithm as seen here on this website:
//https://0fps.net/2013/07/03/ambient-occlusion-for-minecraft-like-worlds/
uint8_t Chunk_Mesh::getVertexAmbientOcc(bool side1, bool side2, bool corner)
{
    if (side1 && side2)
    {
        return 0;
    }
    else
    {
        return 3 - (side1 + side2 + corner);
    }
}



void Chunk_Mesh::addBlockIndices()
{
    GLuint& i = m_activePart->indicesCount;

    m_activePart->indices.insert(m_activePart->indices.end(),
    {
        0 + i, 1 + i, 2 + i,
        2 + i, 3 + i, 0 + i
    });

    i += 4;
}

//This makes a sorta X shape
void Chunk_Mesh::addPlantToMesh(float x, float y, float z, const Block::Block_Data& block)
{
    m_activePart = &m_floraPart;
    m_activePart->vertexCoords.insert(m_activePart->vertexCoords.end(),
    {
        x,      y,      z,
        x + 1,  y,      z + 1,
        x + 1,  y + 1,  z + 1,
        x,      y + 1,  z,

        x,      y,      z + 1,
        x + 1,  y,      z,
        x + 1,  y + 1,  z,
        x,      y + 1,  z + 1,
    });

    finishBlockFace(block.getTextureSide(), Light_Value::SIDE);
    finishBlockFace(block.getTextureSide(), Light_Value::SIDE);
}

#include "CMesh_Builder.h"

#include <GL/glew.h>
#include <iostream>

#include <SFML/System.hpp>

#include "CBlock.h"
#include "CSection.h"
#include "CFull_Chunk.h"
#include "../Block/Block_Database.h"

#include "../../Util/Log.h"

namespace
{
    const std::vector<GLfloat> frontFace
    {
        0,          0,          BLOCK_SIZE,
        BLOCK_SIZE, 0,          BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
        0,          BLOCK_SIZE, BLOCK_SIZE
    };

    const std::vector<GLfloat> backFace
    {
        BLOCK_SIZE, 0,          0,
        0,          0,          0,
        0,          BLOCK_SIZE, 0,
        BLOCK_SIZE, BLOCK_SIZE, 0
    };

    const std::vector<GLfloat> leftFace
    {
        0, 0,           0,
        0, 0,           BLOCK_SIZE,
        0, BLOCK_SIZE,  BLOCK_SIZE,
        0, BLOCK_SIZE,  0
    };

    const std::vector<GLfloat> rightFace
    {
        BLOCK_SIZE, 0,          BLOCK_SIZE,
        BLOCK_SIZE, 0,          0,
        BLOCK_SIZE, BLOCK_SIZE, 0,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE
    };

    const std::vector<GLfloat> topFace
    {
        0,          BLOCK_SIZE, BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, 0,
        0,          BLOCK_SIZE, 0
    };

    const std::vector<GLfloat> bottomFace
    {
        0,          0, 0,
        BLOCK_SIZE, 0, 0,
        BLOCK_SIZE, 0, BLOCK_SIZE,
        0,          0, BLOCK_SIZE
    };

    constexpr GLfloat TOP_LIGHT      = 1.0f;
    constexpr GLfloat X_LIGHT        = 0.8f;
    constexpr GLfloat Z_LIGHT        = 0.6f;
    constexpr GLfloat BOTTOM_LIGHT   = 0.6f;
}


namespace Chunk
{
    Mesh_Builder::Mesh_Builder(const Section& section)
    :   mp_section (&section)
    { }

    float sum = 0;
    int n = 0;

    void Mesh_Builder::setActiveMesh(Meshes& meshes)
    {
        //m_pActiveMesh = &meshes.solidMesh;
        //return;


        ///@TODO For some reason, flora and liquid meshes will only work when there is a solid block
        switch(mp_activeData->meshType)
        {
            case Block::Mesh_Type::Solid:
                m_pActiveMesh = &meshes.solidMesh;
                break;

            case Block::Mesh_Type::Flora:
                m_pActiveMesh = &meshes.floraMesh;
                break;

            case Block::Mesh_Type::Liquid:
                m_pActiveMesh = &meshes.liquidMesh;
                break;
        }
    }


    //Looks at the faces of every block, and adds block faces to a mesh if said face
    //is non-opaque (Other checks are done too)
    void Mesh_Builder::generateMesh(Meshes& meshes)
    {
        n++;
        sf::Clock timer;
        meshes.floraMesh.reset();

        meshes.solidMesh.reset();
        meshes.liquidMesh.reset();

        //Local direction vectors
        //This is used in the if statements below
        Block::Small_Position up;
        Block::Small_Position down;
        Block::Small_Position left;
        Block::Small_Position right;
        Block::Small_Position front;
        Block::Small_Position back;

        for (int8_t y = 0; y < CHUNK_SIZE; ++y)
        {
            if (!shouldCreateLayer(y))
            {
                continue;
            }
            for (int8_t x = 0; x < CHUNK_SIZE; ++x)
            {
                for (int8_t z = 0; z < CHUNK_SIZE; ++z)
                {
                    Block::Small_Position blockPosition(x, y, z);
                    if(mp_section->qGetBlock(blockPosition) == Block::ID::Air)
                        continue;

                    mp_activeData = &mp_section->qGetBlock(blockPosition).getData();

                    //Set local block position vectors.
                    //This is mostly to make the if statements below to look neater.
                    up      =   {       x,      int8_t( y + 1),     z};
                    down    =   {       x,      int8_t( y - 1),     z};
                    left    =   {int8_t(x - 1),         y,          z};
                    right   =   {int8_t(x + 1),         y,          z};
                    front   =   {       x,              y, int8_t(  z + 1)};
                    back    =   {       x,              y, int8_t(  z - 1)};

                    //Set the active mesh (Solid blocks, liquid blocks, flora blocks)
                    setActiveMesh(meshes);

                    //Add faces to the chunk's mesh where the adjacent block is non-opaque
                    //Y-Faces
                    tryAddFace(topFace, mp_activeData->topTextureCoords,
                               blockPosition, up, TOP_LIGHT);

                    tryAddFace(bottomFace, mp_activeData->bottomTextureCoords,
                               blockPosition, down, BOTTOM_LIGHT);
                    //X-Faces
                    tryAddFace(rightFace, mp_activeData->sideTextureCoords,
                               blockPosition, right, X_LIGHT);

                    tryAddFace(leftFace, mp_activeData->sideTextureCoords,
                               blockPosition, left, X_LIGHT);
                    //Z-Faces
                    tryAddFace(frontFace, mp_activeData->sideTextureCoords,
                               blockPosition, front, Z_LIGHT);

                    tryAddFace(backFace, mp_activeData->sideTextureCoords,
                               blockPosition, back, Z_LIGHT);
                }
            }
        }

        auto timeForGen = timer.getElapsedTime().asSeconds();
        sum += timeForGen;


        LOG("Chunk mesh made in:    %.3f ms!\nAverage:                %.3f ms \n\n",
            timeForGen * 1000.0f, (sum / n) * 1000.0f);

/*

        std::cout   << "Chunk section created in: "   << timeForGen   * 1000.0f << "ms" <<  "\n"
                    << "Average: "                    << (sum / n)    * 1000.0f << "ms\n\n";
*/
    }

    void Mesh_Builder::tryAddFace(const std::vector<GLfloat>& face,
                                  const Vector2& textureCoords,
                                  const Block::Small_Position& thisBlockPos,
                                  Block::Small_Position& adjacentBlockPosition,
                                  GLfloat cardinalLight)
    {
        if (shouldMakeFaceAdjTo(adjacentBlockPosition))
        {
            m_pActiveMesh->addFace(face,
                                   Block::Database::get().textures.getTextureCoords(textureCoords),
                                   cardinalLight,
                                   mp_section->getPosition(),
                                   thisBlockPos);
        }
    }


    //Looks at a layer of chunk
    //Returns true if the layer itself, or an adjacent one, has a non-opaque block
    //I do this as it saves ALOT of time when iterating through underground chunks, which typically get skipped
    //thanks to this function (reduction, on my laptop, from >5ms to <0.5ms average chunk mesh gen time)
    bool Mesh_Builder::shouldCreateLayer(uint32_t yPosition)
    {
        auto hasAdjLayerGotTranslucentBlock = [&](int32_t xd, int32_t zd)
        {
            const Section* c = mp_section->getAdjacentSection({xd, zd});
            if(!c)
            {
                return true;
            }
            else
            {
                return c->getLayer(yPosition).opaqueCount < CHUNK_AREA;
            }
        };

        return mp_section->getLayer             (yPosition)      .opaqueCount < CHUNK_AREA ||
               mp_section->getLayer             (yPosition + 1)  .opaqueCount < CHUNK_AREA ||
               mp_section->getLayer             (yPosition - 1)  .opaqueCount < CHUNK_AREA ||
               hasAdjLayerGotTranslucentBlock   ( 1,  0) ||
               hasAdjLayerGotTranslucentBlock   (-1,  0) ||
               hasAdjLayerGotTranslucentBlock   ( 0, -1) ||
               hasAdjLayerGotTranslucentBlock   ( 0,  1);
    }




    bool Mesh_Builder::shouldMakeFaceAdjTo(Block::Small_Position& pos) const
    {
        auto block = mp_section->getBlock(pos);
        const Block::Data_Holder& data = block.getData();

        if (block == Block::ID::Air)
        {
            return true;
        }
        else if ((data.blockID != mp_activeData->blockID) &&
                 !data.isOpaque)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

#include "CMesh_Builder.h"

#include <GL/glew.h>
#include <iostream>

#include <SFML/System.hpp>

#include "CBlock.h"
#include "CSection.h"
#include "CFull_Chunk.h"
#include "../Block/Block_Database.h"

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


    void Mesh_Builder::generateMesh(Meshes& meshes)
    {
        n++;
        sf::Clock timer;
        meshes.floraMesh.reset();
        meshes.solidMesh.reset();
        meshes.liquidMesh.reset();

        uint32_t faces = 0;

        auto& atlas = Block::Database::get().textures;

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


                    Chunklet_Position position = mp_section->getPosition();

                    //Set local block position vectors
                    Block::Small_Position up    (x, int8_t(y + 1), z);
                    Block::Small_Position down  (x, int8_t(y - 1), z);

                    Block::Small_Position left  (int8_t(x - 1), y, z);
                    Block::Small_Position right (int8_t(x + 1), y, z);

                    Block::Small_Position front  (x, y, int8_t(z + 1));
                    Block::Small_Position back   (x, y, int8_t(z - 1));

                    //Set the active mesh (Solid blocks, liquid blocks, flora blocks)
                    setActiveMesh(meshes);

                    //Y-Faces
                    if (shouldMakeFaceAdjTo(up))
                    {
                        m_pActiveMesh->addFace(topFace,
                                               atlas.getTextureCoords(mp_activeData->topTextureCoords),
                                               TOP_LIGHT,
                                               position,
                                               blockPosition);
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(down))
                    {
                        m_pActiveMesh->addFace(bottomFace,
                                               atlas.getTextureCoords(mp_activeData->bottomTextureCoords),
                                               BOTTOM_LIGHT,
                                               position,
                                               blockPosition);

                        faces++;
                    }

                    //X-Faces
                    if (shouldMakeFaceAdjTo(right))
                    {
                        m_pActiveMesh->addFace(rightFace,
                                               atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                               X_LIGHT,
                                               position,
                                               blockPosition);
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(left))
                    {
                        m_pActiveMesh->addFace(leftFace,
                                               atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                               X_LIGHT,
                                               position,
                                               blockPosition);
                        faces++;
                    }

                    //Z-Faces
                    if (shouldMakeFaceAdjTo(front))
                    {
                        m_pActiveMesh->addFace(frontFace,
                                                 atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                                 Z_LIGHT,
                                                 position,
                                                 blockPosition);
                        faces++;
                    }

                    if (shouldMakeFaceAdjTo(back))
                    {
                        m_pActiveMesh->addFace(backFace,
                                                 atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                                 Z_LIGHT,
                                                 position,
                                                 blockPosition);
                        faces++;
                    }

                }
            }
        }

        auto timeForGen = timer.getElapsedTime().asSeconds();
        sum += timeForGen;
        std::cout << "Faces: "      << faces << " created in: " << timeForGen * 1000.0f << "ms" <<  "\n";
        std::cout << "Average: "    << (sum / n) * 1000.0f << "ms\n\n";
    }

    //Looks at a layer of chunk
    //Returns true if the layer itself, or an adjacent one, has a non-opaque block
    //I do this as it saves ALOT of time when iterating through underground chunks, which typically get skipped
    //thanks to this function (reduction, on my laptop, from >5ms to <1ms average chunk mesh gen time)
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



























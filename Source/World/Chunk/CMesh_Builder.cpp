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

    void Mesh_Builder::generateMesh(Meshes& meshes)
    {
        n++;
        sf::Clock timer;
        meshes.liquidMesh.reset();
        meshes.solidMesh.reset();

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
                    if(mp_section->qGetBlock(blockPosition) == 0)
                        continue;

                    mp_activeData = &mp_section->qGetBlock(blockPosition).getData();

                    Chunklet_Position position = mp_section->getPosition();

                    Block::Small_Position up    (x, int8_t(y + 1), z);
                    Block::Small_Position down  (x, int8_t(y - 1), z);

                    Block::Small_Position left  (int8_t(x - 1), y, z);
                    Block::Small_Position right (int8_t(x + 1), y, z);

                    Block::Small_Position front  (x, y, int8_t(z + 1));
                    Block::Small_Position back   (x, y, int8_t(z - 1));

                    //Y-Faces
                    if (shouldMakeFaceAdjTo(up))
                    {
                        meshes.solidMesh.addFace(topFace,
                                                 atlas.getTextureCoords(mp_activeData->topTextureCoords),
                                                 TOP_LIGHT,
                                                 position,
                                                 blockPosition);
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(down))
                    {
                        meshes.solidMesh.addFace(bottomFace,
                                                 atlas.getTextureCoords(mp_activeData->bottomTextureCoords),
                                                 BOTTOM_LIGHT,
                                                 position,
                                                 blockPosition);

                        faces++;
                    }

                    //X-Faces
                    if (shouldMakeFaceAdjTo(right))
                    {
                        meshes.solidMesh.addFace(rightFace,
                                                 atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                                 X_LIGHT,
                                                 position,
                                                 blockPosition);
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(left))
                    {
                        meshes.solidMesh.addFace(leftFace,
                                                 atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                                 X_LIGHT,
                                                 position,
                                                 blockPosition);
                        faces++;
                    }

                    //Z-Faces
                    if (shouldMakeFaceAdjTo(front))
                    {
                        meshes.solidMesh.addFace(frontFace,
                                                 atlas.getTextureCoords(mp_activeData->sideTextureCoords),
                                                 Z_LIGHT,
                                                 position,
                                                 blockPosition);
                        faces++;
                    }

                    if (shouldMakeFaceAdjTo(back))
                    {
                        meshes.solidMesh.addFace(backFace,
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

    bool Mesh_Builder::shouldCreateLayer(uint32_t yPosition)
    {
        //return true;

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
        auto data = block.getData();

        if (block == Block::ID::Air)
        {
            return true;
        }
        ///@TODO do this stuff
        /*
        else if ( data.blockID == m_p_activeBlockData->get().blockID)
        {
            return false;
        }
        else if (!data.isOpaque)
        {
            return true;
        }
        */
        return false;
    }

}



























#include "CMesh_Builder.h"

#include <GL/glew.h>
#include <iostream>

#include <SFML/System.hpp>

#include "CBlock.h"
#include "CSection.h"
#include "../Block/Block_Database.h"

namespace
{
    const std::vector<GLfloat> frontFace
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1
    };

    const std::vector<GLfloat> backFace
    {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0
    };

    const std::vector<GLfloat> leftFace
    {
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0
    };

    const std::vector<GLfloat> rightFace
    {
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1
    };

    const std::vector<GLfloat> topFace
    {
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0
    };

    const std::vector<GLfloat> bottomFace
    {
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };
}


namespace Chunk
{
    Mesh_Builder::Mesh_Builder(const Section& section)
    :   mp_section (&section)
    { }

    void Mesh_Builder::generateMesh(Meshes& meshes)
    {
        sf::Clock timer;
        meshes.liquidMesh.reset();
        meshes.solidMesh.reset();

        uint32_t faces = 0;

        auto& atlas = Block::Database::get().textures;

        for (int8_t y = 0; y < CHUNK_SIZE; ++y){
            for (int8_t x = 0; x < CHUNK_SIZE; ++x){
                for (int8_t z = 0; z < CHUNK_SIZE; ++z)
                {
                    Block::Small_Position blockPosition(x, y, z);
                    if(mp_section->qGetBlock(blockPosition) == 0)
                        continue;

                    mp_activeData = &Block::Database::get().getBlock(mp_section->qGetBlock(blockPosition).id).getData().get();

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
                        meshes.solidMesh.addFace(topFace, position, blockPosition);
                        meshes.solidMesh.addTexCoords(atlas.getTextureCoords(mp_activeData->topTextureCoords));
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(down))
                    {
                        meshes.solidMesh.addFace(bottomFace, position, blockPosition);
                        meshes.solidMesh.addTexCoords(atlas.getTextureCoords(mp_activeData->bottomTextureCoords));
                        faces++;
                    }

                    //X-Faces
                    if (shouldMakeFaceAdjTo(right))
                    {
                        meshes.solidMesh.addFace(rightFace, position, blockPosition);
                        meshes.solidMesh.addTexCoords(atlas.getTextureCoords(mp_activeData->sideTextureCoords));
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(left))
                    {
                        meshes.solidMesh.addFace(leftFace, position, blockPosition);
                        meshes.solidMesh.addTexCoords(atlas.getTextureCoords(mp_activeData->sideTextureCoords));
                        faces++;
                    }

                    //Z-Faces
                    if (shouldMakeFaceAdjTo(front))
                    {
                        meshes.solidMesh.addFace(frontFace, position, blockPosition);
                        meshes.solidMesh.addTexCoords(atlas.getTextureCoords(mp_activeData->sideTextureCoords));
                        faces++;
                    }
                    if (shouldMakeFaceAdjTo(back))
                    {
                        meshes.solidMesh.addFace(backFace, position, blockPosition);
                        meshes.solidMesh.addTexCoords(atlas.getTextureCoords(mp_activeData->sideTextureCoords));
                        faces++;
                    }
                }
            }
        }

        std::cout << "Faces: " << faces << " created in: " << timer.getElapsedTime().asSeconds() * 1000.0f << "ms" <<  "\n";
    }

    ///@TODO finish this function
    bool Mesh_Builder::shouldCreateLayer(uint32_t yPosition)
    {
        auto hasAdjLayerGotTranslucentBlock = [&](int32_t xd, int32_t zd)
        {

        };

        return mp_section->getLayer(yPosition)      .opaqueCount > 0 ||
               mp_section->getLayer(yPosition + 1)  .opaqueCount > 0 ||
               mp_section->getLayer(yPosition - 1)  .opaqueCount > 0;
    }


    bool Mesh_Builder::shouldMakeFaceAdjTo(Block::Small_Position& pos) const
    {
        auto block = mp_section->getBlock(pos);
        auto data = Block::Database::get().getBlock(block.id).getData().get();

        if (block == Block::ID::Air)
        {
            return true;
        }
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



























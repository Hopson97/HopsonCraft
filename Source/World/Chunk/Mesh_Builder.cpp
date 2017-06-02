#include "Mesh_Builder.h"

#include <GL/glew.h>
#include <iostream>

#include <SFML/System.hpp>

#include "Nodes.h"
#include "Section.h"
#include "Full_Chunk.h"
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

    const std::vector<GLfloat> xMesh1
    {
        0,          0,          0,
        BLOCK_SIZE, 0,          BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
        0,          BLOCK_SIZE, 0,
    };

    const std::vector<GLfloat> xMesh2
    {
        0,          0,          BLOCK_SIZE,
        BLOCK_SIZE, 0,          0,
        BLOCK_SIZE, BLOCK_SIZE, 0,
        0,          BLOCK_SIZE, BLOCK_SIZE,
    };

    constexpr GLfloat TOP_LIGHT      = MAX_LIGHT;
    constexpr GLfloat X_LIGHT        = MAX_LIGHT / 1.3;
    constexpr GLfloat Z_LIGHT        = MAX_LIGHT / 1.7;
    constexpr GLfloat BOTTOM_LIGHT   = MAX_LIGHT / 2.2;

    //Small struct to hold the chunk and it's mesh being used for building
    struct ChunkMesh
    {
        ChunkMesh(const Chunk::Section& section, Chunk::Mesh& mesh)
        :   chunk       (section)
        ,   activeMesh  (mesh)
        { }

        const Chunk::Section&   chunk;
        Chunk::Mesh&            activeMesh;
    };


    /*
        Looks at a layer of chunk
        Returns true if the layer itself, or an adjacent one, has a non-opaque block
        I do this as it saves ALOT of time when iterating through underground chunks, which typically get skipped
        thanks to this function (reduction, on my laptop, from >5ms to <0.5ms average chunk mesh gen time)
    */
    bool shouldCreateLayer(int yValue, const Chunk::Section& chunk)
    {
        auto hasAdjLayerGotTranslucentBlock = [&](int32_t xd, int32_t zd)
        {
            const Chunk::Section* c = chunk.getAdjacentSection({xd, zd});
            if(!c)
            {
                return true;
            }
            else
            {
                return c->getLayer(yValue).opaqueCount < CHUNK_AREA;
            }
        };

        return chunk.getLayer             (yValue)      .opaqueCount < CHUNK_AREA ||
               chunk.getLayer             (yValue + 1)  .opaqueCount < CHUNK_AREA ||
               chunk.getLayer             (yValue - 1)  .opaqueCount < CHUNK_AREA ||
               hasAdjLayerGotTranslucentBlock   ( 1,  0) ||
               hasAdjLayerGotTranslucentBlock   (-1,  0) ||
               hasAdjLayerGotTranslucentBlock   ( 0, -1) ||
               hasAdjLayerGotTranslucentBlock   ( 0,  1);
    }

    //Looks at the block data, and sees what type of mesh it belongs to, and then return it
    Chunk::Mesh& getActiveMesh(const Block::Data_Holder& blockData,
                               Chunk::Meshes& meshes)
    {
        switch(blockData.meshType)
        {
            case Block::Mesh_Type::Solid:
                return meshes.solidMesh;

            case Block::Mesh_Type::Flora:
                return meshes.floraMesh;

            case Block::Mesh_Type::Liquid:
                return meshes.liquidMesh;
        }

        return meshes.solidMesh;
    }


    //Adds an X-Shaped mesh into the chunk mesh, for example:
    //  * Rose
    //  * Tall grass
    //  * Spider Webs
    void addXMesh(const Vector2& textureCoords,
                  const Block::Position& thisBlockPos,
                  ChunkMesh& chunkMesh)
    {
        GLfloat natLight   = chunkMesh.chunk.qGetNaturalLight(thisBlockPos);
        GLfloat blockLight = chunkMesh.chunk.qGetBlockLight  (thisBlockPos);

        auto tex = Block::Database::get().getTextureAtlas().getTextureCoords(textureCoords);

        chunkMesh.activeMesh.addFace(xMesh1,
                                     tex,
                                     {X_LIGHT, natLight, blockLight},
                                     chunkMesh.chunk.getPosition(),
                                     thisBlockPos);

        chunkMesh.activeMesh.addFace(xMesh2,
                                     tex,
                                     {X_LIGHT, natLight, blockLight},
                                     chunkMesh.chunk.getPosition(),
                                     thisBlockPos);
    }

    bool shouldMakeFaceAdjacentTo(Block::Position& position,
                                  const Chunk::Section& section,
                                  const Block::Data_Holder& blockData)
    {
        auto  block = section.getBlock(position);
        const Block::Data_Holder& data = block.getData();

        if (block == Block::ID::Air)
        {
            return true;
        }
        else if ((data.blockID != blockData.blockID) &&
                 !data.isOpaque)
        {
            return true;
        }
        else
        {
            return false;
}
    }



    //Adds a single face into the mesh
    void tryAddFaceToMesh(  const std::vector<GLfloat>& face,
                            const Vector2& textureCoords,
                            const Block::Position& thisBlockPos,
                            Block::Position& adjacentBlockPosition,
                            GLfloat cardinalLight,
                            ChunkMesh& chunkMesh,
                            const Block::Data_Holder& blockData)
    {
        const Chunk::Section& chunk = chunkMesh.chunk;

        if (shouldMakeFaceAdjacentTo(adjacentBlockPosition, chunkMesh.chunk, blockData))
        {
            auto natLight   = static_cast<GLfloat>(chunk.getNaturalLight(adjacentBlockPosition));
            auto blockLight = static_cast<GLfloat>(chunk.getBlockLight  (adjacentBlockPosition));
            auto texCoords  = Block::Database::get().getTextureAtlas().getTextureCoords(textureCoords);

            chunkMesh.activeMesh.addFace(face,
                                         texCoords,
                                         {cardinalLight, natLight, blockLight},
                                         chunk.getPosition(),
                                         thisBlockPos);
        }
    }
}

namespace Chunk
{
    struct Direction_Vectors
    {
        //Local direction vectors
        //This is used in the if statements below
        Block::Position up;
        Block::Position down;
        Block::Position left;
        Block::Position right;
        Block::Position front;
        Block::Position back;


        void update(int x, int y, int z)
        {
            up      =   {x,     y + 1,  z};
            down    =   {x,     y - 1,  z};
            left    =   {x - 1, y,      z};
            right   =   {x + 1, y,      z};
            front   =   {x,     y,      z + 1};
            back    =   { x,    y,      z - 1};
        }
    };


    //Looks at the faces of every block, and adds block faces to a mesh if said face
    //is non-opaque (Other checks are done too)
    Meshes buildMesh(const Section& chunk)
    {
        Meshes chunkMeshes;

        static int      n   = 0;
        static float    sum = 0;
        n++;
        sf::Clock timer;

        chunkMeshes.floraMesh.reset();
        chunkMeshes.solidMesh.reset();
        chunkMeshes.liquidMesh.reset();


        const Block::Data_Holder* blockData = nullptr;

        Direction_Vectors vectors;


        for (int8_t y = 0; y < CHUNK_SIZE; ++y)
        {
            if (!shouldCreateLayer(y, chunk))
            {
                continue;
            }
            for (int8_t x = 0; x < CHUNK_SIZE; ++x)
            for (int8_t z = 0; z < CHUNK_SIZE; ++z)
            {
                Block::Position blockPosition(x, y, z);
                auto block = chunk.qGetBlock(blockPosition);
                if (block == Block::ID::Air)
                {
                    continue;
                }

                blockData = &block.getData();

                ChunkMesh chunkMesh(chunk, getActiveMesh(*blockData, chunkMeshes));

                if (blockData->meshStyle == Block::Mesh_Style::XStyle)
                {
                    addXMesh(blockData->bottomTextureCoords,
                             blockPosition,
                             chunkMesh);
                    continue;
                }

                //Set local block position vectors.
                //This is mostly to make the statements below to look neater.
                vectors.update(x, y, z);

                //Y-Faces
                tryAddFaceToMesh(topFace, blockData->topTextureCoords,
                                blockPosition, vectors.up, TOP_LIGHT,
                                chunkMesh, *blockData);

                tryAddFaceToMesh(bottomFace, blockData->bottomTextureCoords,
                                blockPosition, vectors.down, BOTTOM_LIGHT,
                                chunkMesh, *blockData);

                //X-Faces
                tryAddFaceToMesh(rightFace, blockData->sideTextureCoords,
                                blockPosition, vectors.right, X_LIGHT,
                                chunkMesh, *blockData);

                tryAddFaceToMesh(leftFace, blockData->sideTextureCoords,
                                blockPosition, vectors.left, X_LIGHT,
                                chunkMesh, *blockData);

                //Z-Faces
                tryAddFaceToMesh(frontFace, blockData->sideTextureCoords,
                                blockPosition, vectors.front, Z_LIGHT,
                                chunkMesh, *blockData);

                tryAddFaceToMesh(backFace, blockData->sideTextureCoords,
                                blockPosition, vectors.back, Z_LIGHT,
                                chunkMesh, *blockData);
            }
        }

        chunkMeshes.update();

        float timeForGen = timer.getElapsedTime().asSeconds();
        sum += timeForGen;

        LOG("Chunk mesh made in: %.3f ms!\nAverage: %.3f ms \n\n",
            timeForGen * 1000.0f, (sum / n) * 1000.0f);

        return chunkMeshes;
    }
}

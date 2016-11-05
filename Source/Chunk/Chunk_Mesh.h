#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include "Model.h"
#include "OpenGL/GLEW/glew.h"
#include "Block/Block.h"

#include <vector>

class Chunk;

class Chunk_Mesh
{
    struct Chunk_Mesh_Part
    {
        ~Chunk_Mesh_Part(){};
        Model model;
        std::vector<GLfloat> vertexCoords;
        std::vector<GLfloat> textureCoords;

        void addVerticies   (const std::vector<GLfloat>& verticies);
        void addUvCoords    (const std::vector<GLfloat>& coords);
        void buffer         ();
    };

    public:
        Chunk_Mesh (const Chunk& chunk);

        void generateMesh (int height);
        void bufferMesh   ();

        const Chunk_Mesh_Part& getSolidPart() const;
        const Chunk_Mesh_Part& getWaterPart() const;

    private:
        Chunk_Mesh_Part& getPart (Block::ID id);

        void addBlockMesh   (float x, float y, float z, const Block::Block_Base& block );

        bool shouldMakeMesh (int x, int y, int z, const Block::Block_Base& block );

        void addBlockTopToMesh      (float x, float y, float z, const Block::Block_Base& block);
        void addBlockBottomToMesh   (float x, float y, float z, const Block::Block_Base& block);

        void addBlockLeftToMesh     (float x, float y, float z, const Block::Block_Base& block);
        void addBlockRightToMesh    (float x, float y, float z, const Block::Block_Base& block);

        void addBlockFrontToMesh    (float x, float y, float z, const Block::Block_Base& block);
        void addBlockBackToMesh     (float x, float y, float z, const Block::Block_Base& block);

        Chunk_Mesh_Part m_solidPart;
        Chunk_Mesh_Part m_waterPart;

        const Chunk* m_p_chunk;
};

#endif // CHUNK_MESH_H

#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include "Model.h"
#include "Chunk_Layer.h"
#include "OpenGL/GLEW/glew.h"
#include "Block.h"

class Chunk;

struct Chunk_Mesh_Part
{
    Model model;
    std::vector<GLfloat> vertexCoords;
    std::vector<GLfloat> textureCoords;

    void addVerticies   (std::vector<GLfloat> verticies);
    void addUvCoords    (std::vector<GLfloat> coords);
};

class Chunk_Mesh
{
    public:
        Chunk_Mesh (const Chunk& chunk, const std::vector<Chunk_Layer>& layers);

        void generateMesh ();
        void bufferMesh   ();

        const Chunk_Mesh_Part& getSolidPart() const;
        const Chunk_Mesh_Part& getWaterPart() const;

    private:
        void addBlockMesh (float x, float y, float z, const Block::Block_Base& block );

        void addBlockTopToMesh  (float x, float y, float z, const Block::Block_Base& block);
        void addBlockBottomToMesh (float x, float y, float z, const Block::Block_Base& block);

        void addBlockLeftToMesh (float x, float y, float z, const Block::Block_Base& block);
        void addBlockRightToMesh(float x, float y, float z, const Block::Block_Base& block);

        void addBlockFrontToMesh (float x, float y, float z, const Block::Block_Base& block);
        void addBlockBackToMesh  (float x, float y, float z, const Block::Block_Base& block);

        Chunk_Mesh_Part m_solidPart;
        Chunk_Mesh_Part m_waterPart;

        const Chunk* m_p_chunk;
        const std::vector<Chunk_Layer>* m_p_layers;
};

#endif // CHUNK_MESH_H

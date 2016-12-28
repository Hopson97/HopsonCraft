#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include "../../Model/Model.h"

#include <GL/glew.h>

#include "../Block/Block_Type/Block_Type.h"

#include <vector>

class Chunk;
class Chunk_Blocks;

class Chunk_Mesh
{
    struct Chunk_Mesh_Part
    {
        ~Chunk_Mesh_Part(){};
        Model model;
        std::vector<GLfloat> vertexCoords;
        std::vector<GLfloat> textureCoords;
        std::vector<GLfloat> light;
        std::vector<GLfloat> ambientOcclusion;
        std::vector<GLuint>  indices;


        void addUvCoords    (const std::vector<GLfloat>& coords);
        void addLight       (float value);
        void buffer         ();

        GLuint indicesCount = 0;
    };

    public:
        Chunk_Mesh (const Chunk& chunk);

        void generateMesh (int height);
        void bufferMesh   ();

        const Chunk_Mesh_Part& getSolidPart() const;
        const Chunk_Mesh_Part& getWaterPart() const;
        const Chunk_Mesh_Part& getFloraPart() const;

        constexpr static float BLOCK_SIZE = 1.5;

    private:
        Chunk_Mesh_Part& getPart (const Block::Block_Data& block);

        void addBlockMesh   (float x, float y, float z, const Block::Block_Data& block );

        bool shouldCreateLayer(int y) const;
        bool shouldMakeMesh  (int x, int y, int z, const Block::Block_Data& block );

        void addBlockTopToMesh      (float x, float y, float z, const Block::Block_Data& block);
        void addBlockBottomToMesh   (float x, float y, float z, const Block::Block_Data& block);
        void addBlockLeftToMesh     (float x, float y, float z, const Block::Block_Data& block);
        void addBlockRightToMesh    (float x, float y, float z, const Block::Block_Data& block);
        void addBlockFrontToMesh    (float x, float y, float z, const Block::Block_Data& block);
        void addBlockBackToMesh     (float x, float y, float z, const Block::Block_Data& block);

        void    finishBlockFace        (const Vector2& textureLocation, float lightValue);
        uint8_t getVertexAmbientOcc    (bool side1, bool side2, bool corner);

        void addBlockIndices        ();

        void addPlantToMesh         (float x, float y, float z, const Block::Block_Data& block);

        Chunk_Mesh_Part m_solidPart;
        Chunk_Mesh_Part m_waterPart;
        Chunk_Mesh_Part m_floraPart;

        const Chunk*        m_p_chunk;
        const Chunk_Blocks* m_p_chunkBlocks;

        Chunk_Mesh_Part* m_activePart;

        float m_bh;
};

#endif // CHUNK_MESH_H

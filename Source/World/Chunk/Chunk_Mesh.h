#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include "../../Model/Chunk_Model.h"

#include <GL/glew.h>
#include "../Block/Block.h"

#include <vector>

class Chunk;

class Chunk_Mesh
{
    struct Chunk_Mesh_Part
    {
        ~Chunk_Mesh_Part(){};
        Chunk_Model model;
        std::vector<GLfloat> vertexCoords;
        std::vector<GLfloat> textureCoords;
        std::vector<GLfloat> light;
        std::vector<GLuint>  indices;

        void addVerticies   (const std::vector<GLfloat>& verticies);
        void addUvCoords    (const std::vector<GLfloat>& coords);
        void addLight       (float value);
        void addIndices     (const std::vector<GLuint>& index);
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

    private:
        Chunk_Mesh_Part& getPart (const Block_t& block);

        void addBlockMesh   (float x, float y, float z, const Block_t& block );

        inline bool shouldMakeMesh (int x, int y, int z, const Block_t& block );

        void addBlockTopToMesh      (float x, float y, float z, const Block_t& block);
        void addBlockBottomToMesh   (float x, float y, float z, const Block_t& block);
        void addBlockLeftToMesh     (float x, float y, float z, const Block_t& block);
        void addBlockRightToMesh    (float x, float y, float z, const Block_t& block);
        void addBlockFrontToMesh    (float x, float y, float z, const Block_t& block);
        void addBlockBackToMesh     (float x, float y, float z, const Block_t& block);

        void addBlockIndices        ();

        void addPlantToMesh         (float x, float y, float z, const Block_t& block);

        Chunk_Mesh_Part m_solidPart;
        Chunk_Mesh_Part m_waterPart;
        Chunk_Mesh_Part m_floraPart;

        const Chunk* m_p_chunk;

        Chunk_Mesh_Part* m_activePart;
};

#endif // CHUNK_MESH_H

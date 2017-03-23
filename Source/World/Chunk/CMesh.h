#ifndef CMESH_H_INCLUDED
#define CMESH_H_INCLUDED

#include <GL/glew.h>
#include <vector>

#include "CPosition.h"
#include "../Block/Block_Position.h"
#include "../../Model.h"

namespace Chunk
{
    class Mesh
    {
        public:
            void reset();

            void addFace(const std::vector<GLfloat>&    templateFace,
                         const std::vector<GLfloat>&    texCoords,
                         GLfloat                        cardinalLight,
                         const Chunklet_Position&       chunkPos,
                         const Block::Small_Position&   blockPos);

            void buffer();

            const Model& getModel() const;

            uint32_t getFaceCount() const;

        private:
            std::vector<GLfloat> m_verticies;
            std::vector<GLfloat> m_texCoords;
            std::vector<GLfloat> m_cardinalLights;
            std::vector<GLuint> m_indices;

            Model m_model;

            uint32_t m_indicesIndex = 0;
            uint32_t m_facesCount = 0;
    };

    struct Meshes
    {
        Mesh solidMesh;
        Mesh liquidMesh;
    };
}

#endif // CMESH_H_INCLUDED

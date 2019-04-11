#ifndef CMESH_H_INCLUDED
#define CMESH_H_INCLUDED

#include <GL/glew.h>
#include <vector>

#include "Position.h"
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
                         const sf::Vector3<GLfloat>&    light,
                         const Chunklet_Position&       chunkPos,
                         const Block::Position&         localPosition);

            void buffer();

            const Model& getModel() const;

            uint32_t getFaceCount() const;

        private:
            std::vector<GLfloat>    m_verticies;
            std::vector<GLfloat>    m_texCoords;
            std::vector<GLfloat>    m_lights;
            std::vector<GLuint>     m_indices;

            Model m_model;

            uint32_t m_indicesIndex = 0;
            uint32_t m_facesCount = 0;
    };

    struct Meshes
    {
        Mesh solidMesh;
        Mesh floraMesh;
        Mesh liquidMesh;

        int faceCount = 0;
        bool hasFaces = false;

        void update()
        {
            faceCount = solidMesh.getFaceCount() +
                        floraMesh.getFaceCount() +
                        liquidMesh.getFaceCount();
            hasFaces = faceCount > 0;
        }

        void buffer()
        {
            solidMesh    .buffer();
            floraMesh    .buffer();
            liquidMesh   .buffer();
        }
    };
}

#endif // CMESH_H_INCLUDED

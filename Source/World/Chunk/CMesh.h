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
                         const sf::Vector3<GLfloat>&    light,
                         const Chunklet_Position&       chunkPos,
                         const Block::Small_Position&   blockPos);

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

        void buffer()
        {
           solidMesh    .buffer();
           floraMesh    .buffer();
           liquidMesh   .buffer();
        }

        bool hasFaces() const
        {
            return  solidMesh   .getFaceCount() > 0    ||
                    floraMesh   .getFaceCount() > 0    ||
                    liquidMesh  .getFaceCount() > 0;

        }

        uint32_t getFacesCount() const
        {
            return  solidMesh.getFaceCount() +
                    floraMesh.getFaceCount() +
                    liquidMesh.getFaceCount();
        }
    };
}

#endif // CMESH_H_INCLUDED

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
                         const Chunklet_Position&       chunkPos,
                         const Block::Small_Position&   blockPos);

            void addTexCoords(const std::vector<GLfloat>& texCoords);

            void buffer();

            ///@TODO move to .cpp file
            const Model& getModel() const
            {
                return m_model;
            }

        private:
            std::vector<GLfloat> m_verticies;
            std::vector<GLfloat> m_texCoords;
            std::vector<GLuint> m_indices;

            Model m_model;

            uint32_t m_indicesIndex = 0;
    };

    struct Meshes
    {
        Mesh solidMesh;
        Mesh liquidMesh;
    };
}

#endif // CMESH_H_INCLUDED

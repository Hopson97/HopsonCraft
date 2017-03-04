#ifndef CMESH_H_INCLUDED
#define CMESH_H_INCLUDED

#include "../../Model.h"

#include "../Block/Block_Position.h"
#include "../Block/Block_Data.h"

#include "../../Texture/Texture_Atlas.h"

class Chunklet;

namespace Chunk
{
    class Mesh
    {
        class Section
        {
            public:
                void reserve();
                void buffer ();

                void addVerticies   (const std::vector<GLfloat>& v);
                void addTexCoords   (const std::vector<GLfloat>& t);
                void addIndices     (const std::vector<GLuint>&  i);
                void addLightVal    (GLfloat cardinalVal);


                GLuint getIndicesCount() const;

                void addToIndexCount(GLuint amount);

                const Model& getModel() const;

            private:
                std::vector<GLfloat>    m_verticies;
                std::vector<GLfloat>    m_texCoords;
                std::vector<GLuint>     m_indices;
                std::vector<GLfloat>    m_light;

                Model m_model;

                GLuint m_indicesCount = 0;
        };

        public:
            Mesh(Chunklet& chunklet);

            void create();
            void buffer();

            const Section& getSolidMesh() const;


        private:
            bool shouldMakeFaceAdjacentTo(const Block::Small_Position& pos);

            void makeFrontFace  (const Block::Small_Position& pos);
            void makeBackFace   (const Block::Small_Position& pos);
            void makeLeftFace   (const Block::Small_Position& pos);
            void makeRightFace  (const Block::Small_Position& pos);
            void makeTopFace    (const Block::Small_Position& pos);
            void makeBottomFace (const Block::Small_Position& pos);

            Section m_solidMesh;

            Chunklet*         m_p_chunklet        = nullptr;
            const Block::Data*      m_p_activeBlockData = nullptr;
            const Texture::Atlas*   m_p_textureAtlas    = nullptr;
    };
}

#endif // CMESH_H_INCLUDED

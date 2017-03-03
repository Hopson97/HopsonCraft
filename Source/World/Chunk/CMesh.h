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

                inline void addVerticies(const std::vector<GLfloat>& v);
                inline void addTexCoords(const std::vector<GLfloat>& t);
                inline void addIndices  (const std::vector<GLuint>&  i);

                GLuint getIndicesCount() const;

                void addToIndexCount(GLuint amount);

                const Model& getModel() const;

            private:
                std::vector<GLfloat> m_verticies;
                std::vector<GLfloat> m_texCoords;
                std::vector<GLuint>  m_indices;

                Model m_model;

                GLuint m_indicesCount = 0;

        };

        public:
            Mesh(const Chunklet& chunklet);

            void create();

            const Section& getSolidMesh() const;


        private:
            bool shouldMakeFaceAdjacentTo(const Block::Position& pos);

            void makeFrontFace  (const Block::Position& pos);
            void makeBackFace   (const Block::Position& pos);
            void makeLeftFace   (const Block::Position& pos);
            void makeRightFace  (const Block::Position& pos);
            void makeTopFace    (const Block::Position& pos);
            void makeBottomFace (const Block::Position& pos);

            void addIndices(uint32_t faces);


            Section m_solidMesh;

            const Chunklet*         m_p_chunklet        = nullptr;
            const Block::Data*      m_p_activeBlockData = nullptr;
            const Texture::Atlas*   m_p_textureAtlas    = nullptr;
    };
}

#endif // CMESH_H_INCLUDED

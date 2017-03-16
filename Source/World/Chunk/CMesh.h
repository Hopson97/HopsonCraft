#ifndef CMESH_H_INCLUDED
#define CMESH_H_INCLUDED

#include "../../Model.h"
#include "../Block/Block_Position.h"
#include "../../Glm_Common.h"

class Chunklet;

namespace Block
{
    class Data;
};

namespace Texture
{
    class Atlas;
}

namespace Chunk
{
    class Mesh_Section
    {
        public:
            void reset();

            void buffer ();
            void reserve(size_t vert, size_t tex, size_t ind, size_t light);

            void addVerticies   (const std::vector<GLfloat>& v);
            void addTexCoords   (const std::vector<GLfloat>& t);
            void addIndices     (const std::vector<GLuint>&  i);
            void addLightVal    (GLfloat cardinalVal);

            const Model& getModel() const;

            void addIndices();

            uint32_t getFacesCount() const { return m_faces; }

        private:
            uint32_t m_indicesIndex = 0;

            std::vector<GLfloat>    m_verticies;
            std::vector<GLfloat>    m_texCoords;
            std::vector<GLuint>     m_indices;
            std::vector<GLfloat>    m_light;

            Model m_model;

            uint32_t m_faces = 0;
    };

    class Mesh
    {
        public:
            Mesh(Chunklet& chunklet);

            void create();
            void buffer();

            const Mesh_Section& getSolidMesh    () const;
            const Mesh_Section& getLiquidMesh   () const;


        private:
            void setActiveSection();

            bool shouldMakeFaceAdjacentTo(const Block::Small_Position& pos);

            void makeFrontFace  (const Vector3& min, const Vector3& max);
            void makeBackFace   (const Vector3& min, const Vector3& max);
            void makeLeftFace   (const Vector3& min, const Vector3& max);
            void makeRightFace  (const Vector3& min, const Vector3& max);
            void makeTopFace    (const Vector3& min, const Vector3& max);
            void makeBottomFace (const Vector3& min, const Vector3& max);

            Mesh_Section m_solidMesh;
            Mesh_Section m_liquidMesh;
            Mesh_Section* m_activeSection = nullptr;

            Chunklet*               m_p_chunklet        = nullptr;
            const Block::Data*      m_p_activeBlockData = nullptr;
            const Texture::Atlas*   m_p_textureAtlas    = nullptr;
    };
}

#endif // CMESH_H_INCLUDED

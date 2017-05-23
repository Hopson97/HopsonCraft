#ifndef CMESH_BUILDER_H_INCLUDED
#define CMESH_BUILDER_H_INCLUDED

#include <vector>

#include "../../Glm_Common.h"

#include "../Block/Block_Position.h"

#include "CMesh.h"

/*
    This class is owned by every Chunk::Section, and is used to
    build the mesh that makes it up.
*/

namespace Block
{
    class Data_Holder;
}

namespace Chunk
{
    class Section;

    class Mesh_Builder
    {
        public:
            Mesh_Builder(const Section& section);

            void generateMesh(Meshes& meshes);

        private:
            void tryAddFace(const std::vector<GLfloat>& face,
                            const Vector2& textureCoords,
                            const Block::Position& thisBlockPos,
                            Block::Position& adjacentBlockPosition,
                            GLfloat cardinalLight);

            void addXMesh  (const Vector2& textureCoords,
                            const Block::Position& thisBlockPos);

            bool shouldCreateLayer  (uint32_t yPosition);
            bool shouldMakeFaceAdjTo(Block::Position& pos) const;
            void setActiveMesh(Meshes& meshes);

            Mesh*                       m_pActiveMesh;
            const Section*              m_pSection;
            const Block::Data_Holder*   m_pActiveData;


    };
}

#endif // CMESH_BUILDER_H_INCLUDED

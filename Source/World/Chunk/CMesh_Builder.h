#ifndef CMESH_BUILDER_H_INCLUDED
#define CMESH_BUILDER_H_INCLUDED

#include <vector>

#include "../Block/Block_Position.h"

#include "CMesh.h"

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
            bool shouldCreateLayer  (uint32_t yPosition);
            bool shouldMakeFaceAdjTo(Block::Small_Position& pos) const;
            void setActiveMesh(Meshes& meshes);

            Mesh*           m_pActiveMesh;
            const Section*  mp_section;
            const Block::Data_Holder*   mp_activeData;


    };
}

#endif // CMESH_BUILDER_H_INCLUDED

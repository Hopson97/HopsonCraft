#ifndef CMESH_BUILDER_H_INCLUDED
#define CMESH_BUILDER_H_INCLUDED

#include <vector>

#include "../../Glm_Common.h"

#include "../Block/Block_Position.h"

#include "Mesh.h"

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
    class Meshes;

    void buildMesh(const Section& chunk, Meshes& meshes);
}

#endif // CMESH_BUILDER_H_INCLUDED

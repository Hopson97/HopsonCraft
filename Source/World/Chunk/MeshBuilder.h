#ifndef CMeshBuilder_H_INCLUDED
#define CMeshBuilder_H_INCLUDED

#include <vector>

#include "../../Maths/GLM.h"
#include "../Block/BlockPosition.h"
#include "Mesh.h"

/*
    This class is owned by every Chunk::Section, and is used to
    build the mesh that makes it up.
*/

namespace Block
{
    class DataHolder;
}

namespace Chunk
{
    class Section;

    //Meshes buildMesh(const Section& chunk);
}

#endif // CMeshBuilder_H_INCLUDED

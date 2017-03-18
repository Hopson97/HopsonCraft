#ifndef CMESH_BUILDER_H_INCLUDED
#define CMESH_BUILDER_H_INCLUDED

#include <vector>

namespace Chunk
{
    class Section;

    class Mesh_Builder
    {
        public:
            Mesh_Builder(const Section& section);

        private:
            const Section* mp_section;
    };
}

#endif // CMESH_BUILDER_H_INCLUDED

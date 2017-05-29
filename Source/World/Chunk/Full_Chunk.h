#ifndef FULL_CHUNK_H_INCLUDED
#define FULL_CHUNK_H_INCLUDED

#include <vector>

#include "Section.h"

namespace Chunk
{
    class Full_Chunk
    {
        public:

        private:
            std::vector<Section> m_sections;
    };
}

#endif // FULL_CHUNK_H_INCLUDED

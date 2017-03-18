#ifndef CSECTION_H_INCLUDED
#define CSECTION_H_INCLUDED

#include <array>

#include "CPosition.h"
#include "CBlock.h"
#include "../World_Constants.h"

namespace Chunk
{
    class Section
    {
        public:


        private:
            std::array<CBlock, CHUNK_VOLUME> m_blocks;

    };
}

#endif // CSECTION_H_INCLUDED

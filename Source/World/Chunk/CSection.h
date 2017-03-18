#ifndef CSECTION_H_INCLUDED
#define CSECTION_H_INCLUDED

#include <array>

#include "CPosition.h"
#include "CBlock.h"
#include "../World_Constants.h"

struct CLight
{
    CLight()
    :   naturalLight    (0)
    ,   blockLight      (0)
    { }

    uint8_t naturalLight : 4;
    uint8_t blockLight   : 4;
};

namespace Chunk
{
    class Section
    {
        public:


        private:
            std::array<CBlock, Constants::CHUNK_VOLUME> m_blocks;
            std::array<CLight, Constants::CHUNK_VOLUME> m_light;
    };
}

#endif // CSECTION_H_INCLUDED

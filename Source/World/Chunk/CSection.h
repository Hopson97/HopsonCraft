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
            Section(const Chunklet_Position& position);

            void    setBlock(const Block::Small_Position& position, CBlock block);
            CBlock  getBlock(const Block::Small_Position& position);


        private:
            Section* getSection(const Block::Small_Position& position);
            void     checkBound(int8_t dir, int32_t& change);

            uint32_t getIndexFrom(const Block::Small_Position& position);

            std::array<CBlock, Constants::CHUNK_VOLUME> m_blocks;
            std::array<CLight, Constants::CHUNK_VOLUME> m_light;

            Chunklet_Position m_position;
    };
}

#endif // CSECTION_H_INCLUDED

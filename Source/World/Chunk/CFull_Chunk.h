#ifndef CFULL_CHUNK_H_INCLUDED
#define CFULL_CHUNK_H_INCLUDED

#include <vector>

#include "CBlock.h"
#include "CPosition.h"
#include "CSection.h"

class World;

namespace Chunk
{
    class Full_Chunk
    {
        public:
            Full_Chunk(World& world, const Position& position);

            CBlock getBlock(const Block::Position& position);
            const Position& getPosition() const;

        private:
            std::vector<Section> m_chunkSections;

            World* mp_world;
            Position m_position;
    };
}

#endif // CFULL_CHUNK_H_INCLUDED

#ifndef CREGENERATOR_H_INCLUDED
#define CREGENERATOR_H_INCLUDED

#include <unordered_map>
#include <queue>

#include "CPosition.h"
#include "Chunklet.h"

namespace Chunk
{
    class Regenerator
    {
        public:
            void addChunklet(Chunklet& chunklet);
            void addChunklets(std::vector<Chunklet*> chunklets);

            void regen();
            void rebuffer();

        private:
            std::unordered_map<Chunklet_Position, Chunklet*> m_chunklets;
    };
}

#endif // CREGENERATOR_H_INCLUDED

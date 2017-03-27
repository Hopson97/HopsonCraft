#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <vector>
#include <memory>

#include "CSection.h"
#include "CFull_Chunk.h"

namespace Chunk
{
    class Map
    {
        public:
            void addChunk(const Chunk::Position& position, World& world);

            Full_Chunk* get (const Chunk::Position& position);
            bool existsAt   (const Chunk::Position& position);
            Section* get    (const Chunk::Chunklet_Position& position);

            std::unordered_map<Position, Full_Chunk>& getChunks() { return m_chunksMap; }

        private:

            std::unordered_map<Position, Full_Chunk> m_chunksMap;
    };
}

#endif // CMAP_H_INCLUDED

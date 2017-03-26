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
            bool existsAt   (const Chunk::Chunklet_Position& position);

        private:
            std::unordered_map<Chunk::Position, Full_Chunk> m_chunks;

            std::vector<Full_Chunk> m_chunksVector;
            int32_t m_xOffset = 0;
            int32_t m_zOffset = 0;
    };
}

#endif // CMAP_H_INCLUDED

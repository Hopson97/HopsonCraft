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
            Map(int32_t renderDistance);

            void addChunk(const Chunk::Position& position, World& world);

            Full_Chunk* get (const Chunk::Position& position);
            bool existsAt   (const Chunk::Position& position);


            Section* get    (const Chunk::Chunklet_Position& position);

            std::vector<Full_Chunk>& getChunks() { return m_chunksVector; }

        private:
            int32_t getIndex(const Chunk::Position& position);

            std::vector<Full_Chunk> m_chunksVector;
            int32_t m_xOffset = 0;
            int32_t m_zOffset = 0;

            int32_t m_currRenderDistance;
    };
}

#endif // CMAP_H_INCLUDED

#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>

#include "CSection.h"
#include "CFull_Chunk.h"

#include "../Generators/Chunk_Generator.h"


class World_Settings;

namespace Chunk
{
    class Map
    {
        public:
            Map(World& world);

            void addChunk(const Chunk::Position& position, bool populateBlocks);

            Full_Chunk* get (const Chunk::Position& position);
            Section*    get (const Chunk::Chunklet_Position& position);

            bool existsAt   (const Chunk::Position& position) const;

            std::unordered_map<Position, Full_Chunk>& getChunks();

        private:


            void addChunk(std::unordered_map<Position, Full_Chunk>& map,
                          const Chunk::Position& position,
                          bool populateBlocks);

            std::unordered_map<Position, Full_Chunk> m_chunksMap;
            std::unordered_map<Position, Full_Chunk> m_tempChunks;
            World* mp_world = nullptr;

            Chunk_Generator m_chunkGenerator;

            std::mutex m_chunkAddMutex;
    };
}

#endif // CMAP_H_INCLUDED

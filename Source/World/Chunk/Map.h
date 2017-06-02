#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <vector>
#include <memory>

#include "Section.h"
#include "Full_Chunk.h"

#include "../Generators/Terrain_Generator.h"


class World_Settings;
class World_File;

namespace Chunk
{
    class Map
    {
        public:
            Map(World& world);

            void addChunk       (const Chunk::Position& position, bool populateBlocks);
            void deleteChunk    (const Chunk::Position& position, World_File& worldFile);

            const Full_Chunk* get (const Chunk::Position& position)             const;
            const Section*    get (const Chunk::Chunklet_Position& position)    const;

            Full_Chunk& editableGet (const Chunk::Position& position);
            Section*    editableGet (const Chunk::Chunklet_Position& position);

            bool existsAt   (const Chunk::Position& position) const;

            std::unordered_map<Position, Full_Chunk>& getChunks();

        private:
            void addChunk(std::unordered_map<Position, Full_Chunk>& map,
                          const Chunk::Position& position,
                          bool populateBlocks);

            std::unordered_map<Position, Full_Chunk> m_chunksMap;
            std::unordered_map<Position, Full_Chunk> m_tempChunks;
            World* m_pWorld = nullptr;

            Terrain_Generator m_chunkGenerator;
    };
}

#endif // CMAP_H_INCLUDED

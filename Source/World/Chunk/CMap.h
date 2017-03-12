#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <memory>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <queue>


#include "CColumn.h"
#include "CPosition.h"
#include "CRegenerator.h"

class Camera;
class World_File;

namespace Renderer
{
    class Master;
}

namespace Chunk
{
    class Map
    {
        public:
            Map(const Camera& camera, World_File& file);
            ~Map();

            void update();
            void draw(Renderer::Master& renderer, const Camera& camera);

            void addChunk(const Position& position);
            const Column* getChunk(const Chunk::Position& position) const;
            Column* getChunk(const Chunk::Position& position);

            CBlock getBlockAt(const Vector3& worldPosition);

            void breakBlock (const Vector3& worldPosition);
            void placeBlock (const Vector3& worldPosition, CBlock block);

        private:
            void triggerBlocks(const Block::Column_Position& worldPosition);

            void manageChunks();
            void loadAndGenChunks();
            void flagChunks();

            std::unordered_map<Position, std::unique_ptr<Column>> m_chunks;

            Regenerator m_regenerator;

            const Camera* m_p_camera;

            World_File* m_p_worldFile;

            std::atomic<bool> m_isRunning;

            std::mutex m_addChunkMutex;
            std::vector<std::unique_ptr<std::thread>> m_chunkGenThreads;
    };
}

#endif // CMAP_H_INCLUDED

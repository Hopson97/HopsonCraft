#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <unordered_map>
#include <memory>
#include <mutex>
#include <thread>

#include "Chunk/Chunk.h"
#include "Texture/Texture_Atlas.h"

class Camera;
class Master_Renderer;
struct Area;

class Chunk_Map
{
    public:
        Chunk_Map   (const Chunk_Location& playerPosition);
        ~Chunk_Map  ();
        Chunk* getChunkAt (const Chunk_Location& location);
        void addChunk(const Chunk_Location& location);

        void checkChunks ();
        void draw(Master_Renderer& renderer);

        void setBlock (Block::Block_Base& block, const Vector3& worldPosition);
        void setBlocks(Block::Block_Base& block, const std::vector<Vector3> worldPositions);

        bool isSolidBlockAt (const Vector3& worldPosition);

        void makeExplosion  (const Vector3& worldPosition, int power);

        const Block::Block_Base& getBlockAt(const Vector3& worldPosition);

        void saveChunks();

    private:
        void updateChunks   ();
        void deleteChunks   ();

        void manageChunks  ();
        void generateChunks         (const Area& createArea);
        void flagChunksForDelete    (const Area& deleteArea);
        void generateMeshes         (const Area& generationArea);

    private:
        std::unordered_map<Chunk_Location, std::unique_ptr<Chunk>> m_chunks;
        std::vector<Chunk*> m_chunksToUpdate;

        Texture_Atlas   m_blockTextures;
        bool m_isRunning = true;

        unsigned m_renderDistance        = 20;

        unsigned m_generationDistance    = 1;
        unsigned m_loadingDistance       = 1;

        const Chunk_Location* m_playerPosition;

        std::thread m_chunkManageThread;
};

#endif // CHUNK_MAP_H

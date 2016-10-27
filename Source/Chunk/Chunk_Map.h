#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <unordered_map>
#include <memory>
#include <mutex>

#include "Chunk/Chunk.h"
#include "Texture/Texture_Atlas.h"

class Camera;
class Master_Renderer;
struct RenderArea;

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

    private:
        void updateChunks   ();
        void deleteChunks   ();

        void manageChunks  ();
        void generateChunks (const RenderArea& area);
        void checkChunks    (const RenderArea& area);


    private:
        std::unordered_map<Chunk_Location, std::unique_ptr<Chunk>> m_chunks;
        std::vector<Chunk*> m_chunksToUpdate;

        Texture_Atlas   m_blockTextures;
        bool m_isRunning = true;

        int m_renderDistance    = 22;
        int m_loadingDistance   = 1;

        const Chunk_Location* m_playerPosition;

        std::mutex m_accessMutex;
};

#endif // CHUNK_MAP_H

#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <unordered_map>
#include <memory>
#include <thread>

#include "Chunk.h"
#include "../../Texture/Texture_Atlas.h"

namespace sf
{
    class Event;
}

class   Entity;
class   Master_Renderer;
class   Area;
class   World;

class Chunk_Map
{
    public:
        Chunk_Map   (const Chunk_Location& playerPosition,
                     const std::string& worldName,
                     uint32_t seed,
                     World& world);

        ~Chunk_Map  ();

        Chunk* getChunkAt (const Chunk_Location& location);
        const Chunk* getChunkAt (const Chunk_Location& location) const;

        void addChunk(const Chunk_Location& location);

        void checkChunks ();
        void draw(Master_Renderer& renderer);

        void addBlock (const Block::Block_Type& block, const Vector3& worldPosition);
        void addBlocks(const Block::Block_Type& block, const std::vector<Vector3> worldPositions);

        void breakBlock(const Block::Block_Type& block, const Vector3& worldPosition);

        bool isSolidBlockAt (const Vector3& worldPosition);

        void makeExplosion  (const Vector3& worldPosition, int power);

        const Block::Block_Type& getBlockAt(const Vector3& worldPosition);

        void saveChunks() const;

        void addChangedChunk(Chunk* chunk);

    private:
        void deleteChunks   ();
        void updateChunks   ();
        void regenChunks    ();

        void manageChunks   ();
        void generateChunks         (const Area& createArea);
        void flagChunksForDelete    (const Area& deleteArea);
        void generateMeshes         (const Area& generationArea);

    private:
        std::unordered_map<Chunk_Location, std::unique_ptr<Chunk>> m_chunks;
        std::vector<Chunk*> m_chunksToUpdate;

        std::vector<Chunk_Location> m_chunksToDelete;

        Texture_Atlas   m_blockTextures;
        bool m_isRunning = true;

        uint32_t m_generationDistance    = 1;
        uint32_t m_loadingDistance       = 1;

        const Chunk_Location* m_playerPosition;

        std::string m_worldName;
        uint32_t   m_worldSeed;

        World* m_p_world;
};

#endif // CHUNK_MAP_H

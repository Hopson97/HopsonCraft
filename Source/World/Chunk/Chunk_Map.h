#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <unordered_map>
#include <memory>
#include <mutex>
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
class   Settings;

class Chunk_Map
{
    public:
        Chunk_Map   (const Chunk_Location& playerPosition,
                     const std::string& worldName,
                     uint32_t seed,
                     Settings& settings);

        ~Chunk_Map  ();

        Chunk* getChunkAt (const Chunk_Location& location);
        void addChunk(const Chunk_Location& location);

        void input(const sf::Event& e); //temp

        void checkChunks ();
        void draw(Master_Renderer& renderer);

        void setBlock (const Block::Block_Type& block, const Vector3& worldPosition);
        void setBlocks(const Block::Block_Type& block, const std::vector<Vector3> worldPositions);

        bool isSolidBlockAt (const Vector3& worldPosition);

        void makeExplosion  (const Vector3& worldPosition, int power);

        const Block::Block_Type& getBlockAt(const Vector3& worldPosition);

        void saveChunks();

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

        unsigned m_generationDistance    = 1;
        unsigned m_loadingDistance       = 1;

        const Chunk_Location* m_playerPosition;

        std::thread m_chunkManageThread;

        std::string m_worldName;
        uint32_t   m_worldSeed;

        Settings* m_p_settings;


};

#endif // CHUNK_MAP_H

#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
#include <memory>
#include <vector>

#include "Chunk_Location.h"

#include "../Block/Block.h"
#include "../Block/Block_Location.h"

#include "../Gen/World_Generator.h"

#include "Chunk_Location.h"
#include "Chunk_Mesh.h"
#include "Chunk_Layer.h"
#include "Chunk_Blocks.h"

class Texture_Atlas;
class World;
class Chunk_Map;

class Chunk;
typedef std::unique_ptr<Chunk> Chunk_Ptr;

class Chunk
{
    public:
        Chunk(const Chunk_Location& position,
              Chunk_Map& chunkMap,
              const Texture_Atlas& blockAtlas,
              unsigned seed,
              const std::string& worldName);

        bool hasBlockData   () const;
        bool hasMesh        () const;
        bool hasBuffered    () const;

        void generateMesh   ();
        void bufferMesh     ();

        const Texture_Atlas& getAtlas () const;

        const Chunk_Location& getLocation () const;
        const Vector2&  getPosition () const;

        Chunk_Blocks& getBlocks();
        const Chunk_Blocks& getBlocks() const;

        const Chunk_Mesh& getMesh() const;

        void giveDeleteFlag (const std::string& worldName);
        bool hasDeleteFlag  () const;

        void update         ();
        void giveUpdateFlag ();
        bool hasUpdateFlag  () const;

        void saveToFile     (const std::string& worldName);

        static constexpr int SIZE  = 20,
                             WATER_LEVEL = 90,
                             BEACH_LEVEL = WATER_LEVEL + 3,
                             SNOW_LEVEL = 260;

    private:
        void loadBlockData          (const std::string& worldName);
        std::string getFileString   (const std::string& worldName);

    private:
        Chunk_Location m_location; //Map coords
        Vector2  m_position; //GL coords

        Chunk_Map* m_p_chunkMap;

        const Texture_Atlas* m_p_atlas;

        bool m_hasBlockData     = false;
        bool m_hasMesh          = false;
        bool m_hasBuffered      = false;

        bool m_hasDeleteFlag    = false;
        bool m_hasUpdateFlag    = false;

        Chunk_Mesh m_mesh;

        Chunk_Blocks m_blocks;

        World_Generator m_worldGenerator;
};


#endif // CHUNK_H

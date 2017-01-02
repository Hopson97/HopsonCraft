#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
#include <memory>
#include <vector>

#include "Chunk_Location.h"

#include "../Block/Block_Type/Block_Type.h"
#include "../Block/Block_Location.h"
#include "../Block/Updateable/Updatable_Block.h"

#include "../Gen/World_Generator.h"

#include "Chunk_Location.h"
#include "Chunk_Mesh.h"
#include "Chunk_Layer.h"
#include "Chunk_Blocks.h"

#include "../../Entity.h"

class Texture_Atlas;
class Chunk_Map;
class World;

namespace Block
{
    class Block_Type;
}

class Chunk : public Entity
{
    public:
        Chunk(const Chunk_Location& position,
              Chunk_Map& chunkMap,
              const Texture_Atlas& blockAtlas,
              unsigned seed,
              const std::string& worldName);

        void addBlock(const Block_Location& location,
                      const Block::Block_Type& block,
                      bool overrideBlocks = true);

        void breakBlock(const Block_Location& location,
                        World& world,
                        const Vector3& worldPosition,
                        Block::Break_Type breakType);

        bool tick   ();
        bool update ();

        bool hasBlockData   () const;
        bool hasMesh        () const;
        bool hasBuffered    () const;

        void generateMesh   ();
        void bufferMesh     ();

        const Texture_Atlas& getAtlas       () const;

        const Chunk_Location& getLocation   () const;
        const Vector2  getPosition          () const;

        const Chunk_Blocks& getBlocks       () const;
        const Chunk_Blocks* getAdjBlocks    (int xd, int zd) const;
        Chunk_Blocks* getAdjBlocks          (int xd, int zd);

        const Chunk_Mesh& getMesh   () const;

        void giveDeleteFlag (const std::string& worldName);
        bool hasDeleteFlag  () const;

        void regenMesh          (bool regenNeighbours = true);
        void giveRegenMeshFlag  ();
        bool hasRegenMeshFlag   () const;

        void saveToFile         (const std::string& worldName) const;

        const Matrix4& getModelMatrix   () const;

        Chunk* getChunkAdj (int dx, int dz) const;

        uint8_t getNaturalLight (const Block_Location& location) const;
        uint8_t getBlockLight   (const Block_Location& location) const;

        void resetLight();

    private:
        Chunk_Blocks& getBlocks_nc ();

        void floodFillLight();

        void loadBlockData              (const std::string& worldName);
        std::string getFileString       (const std::string& worldName) const;

        std::unordered_map<Block_Location, std::unique_ptr<Updatable_Block>> m_updatableBlocks;
        std::unordered_map<Block_Location, const Block::Block_Type*> m_addedBlocks;

        Chunk_Location m_location; //Map coords

        Chunk_Map* m_p_chunkMap;

        const Texture_Atlas* m_p_atlas;

        bool m_hasBlockData         = false;
        bool m_hasMesh              = false;
        bool m_hasBuffered          = false;

        bool m_hasDeleteFlag        = false;
        bool m_hasregenMeshFlag     = false;

        bool m_calculatedLight      = false;

        bool m_hasGenBaseBlockData = false;

        Chunk_Mesh m_mesh;
        Chunk_Blocks m_blocks;
        World_Generator m_worldGenerator;
        Matrix4 m_modelMatrix;
};

typedef std::unique_ptr<Chunk> Chunk_Ptr;

#endif // CHUNK_H

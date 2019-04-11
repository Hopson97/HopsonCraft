#ifndef CSECTION_H_INCLUDED
#define CSECTION_H_INCLUDED

#include <array>
#include <atomic>

#include "../World_Constants.h"

#include "Position.h"
#include "Nodes.h"
#include "Mesh_Builder.h"
#include "../Block/Block_Database.h"
#include "../../Physics/AABB.h"

#include "../IBlock_Accessible.h"

#include "../../Util/Array3D.h"

class World_File;

namespace Chunk
{
    class Map;
    class Full_Chunk;

    class Section : public IBlock_Accessible
    {
        struct State
        {
            State()
            :   made    (false)
            ,   buffered(false)
            { }

            bool made;
            bool buffered;
        };

        struct Placed_Blocked
        {
            Placed_Blocked(CBlock b, uint16_t i)
            :   block   (b)
            ,   index   (i) {}

            CBlock block;
            uint16_t index;
        };

        //This struct helps with optimizing the creation of the mesh
        struct Layer
        {
            int16_t opaqueCount = 0;

            Layer() = default;

            void update(CBlock block)
            {
                block.getData().isOpaque ?
                    opaqueCount++ :
                    opaqueCount--;

                if (opaqueCount < 0)
                {
                    opaqueCount = 0;
                }
            }
        };

        const static Layer errorLayer;

        public:
            Section(const Chunklet_Position& position, Map& map, Full_Chunk& fullChunk);

            Section              (const Section& other) = delete;
            Section& operator=   (const Section& other) = delete;

            Section              (Section&& other) = default;
            Section& operator=   (Section&& other) = default;

            ~Section() = default;

            const State& getStates() const;

            void makeMesh   ();
            void bufferMesh ();

            void tick(World& world);

            const Chunklet_Position& getPosition()  const;
            const Meshes& getMeshes     ()          const;
            const Layer& getLayer       (int8_t y)  const;

            const Section* getAdjacentSection(const Vector2& change) const;
            const AABB& getAABB() const;
            const Full_Chunk& getParentChunk() const;

            Full_Chunk& getParentChunk();

        private:
            Array3D<CBlock, CHUNK_SIZE>     m_blocks;
            Array3D<CLight, CHUNK_SIZE>     m_light;
            std::array<Layer, CHUNK_SIZE>   m_layerHasAir;
            Meshes m_meshes;
            AABB m_aabb;
            Chunklet_Position m_position;

            Map* m_pChunkMap;
            Full_Chunk* m_parentChunk;

            State m_states;

        public: //Getter/ Setter mess
            //Blocks getters/ Setters with bounds checking
            void    setBlock(Block::Position& position, CBlock block, bool generatedBlock = true);
            CBlock  getBlock(Block::Position& position) const;

            //Blocks getters/ Setters with no bounds checking
            void    qSetBlock(const Block::Position& position, CBlock block, bool generatedBlock = true);
            CBlock  qGetBlock(const Block::Position& position) const;

            //Natural lights getters/ setters with bounds checking
            void setNaturalLight(Block::Position& position, uint8_t value);
            uint8_t getNaturalLight(Block::Position& position) const;

            //Natural lights getters/ setters with no bounds checking
            void qSetNaturalLight(const Block::Position& position, uint8_t value);
            uint8_t qGetNaturalLight(const Block::Position& position) const;

            //Block lights getters/ setters with bounds checking
            void setBlockLight(Block::Position& position, uint8_t value);
            uint8_t getBlockLight(Block::Position& position) const;

            //Block lights getters/ setters with no bounds checking
            void qSetBlockLight(const Block::Position& position, uint8_t value);
            uint8_t qGetBlockLight(const Block::Position& position) const;

            //For the interface
            void    setBlock    (int x, int y, int z, CBlock block) override;
            void    qSetBlock   (int x, int y, int z, CBlock block) override;
            CBlock  qGetBlock   (int x, int y, int z) const override;
            CBlock  getBlock    (int x, int y, int z) const override;

    };
}

#endif // CSECTION_H_INCLUDED

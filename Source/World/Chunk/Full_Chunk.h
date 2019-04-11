#ifndef CFULL_CHUNK_H_INCLUDED
#define CFULL_CHUNK_H_INCLUDED

#include <vector>
#include <memory>
#include <algorithm>

#include "Nodes.h"
#include "Position.h"
#include "Section.h"

#include "../IBlock_Accessible.h"

#include "../../Util/Array2D.h"

/*
    This class is basically the manager for a vertical column of chunks.
    It stores a vector them, and adds more Chunk::Section if a block is
    placed above the current maximum chunk height of this chunk
*/

namespace Renderer
{
    class Master;
}

class World;
class Camera;
class World_Settings;
class World_File;

namespace Chunk
{
    class Map;

    class Full_Chunk : public IBlock_Accessible
    {
        friend class Section;

        public:
            ///@TODO Better solution for this
            bool hasGeneratedBlockData = false;

            Full_Chunk() = default;
            Full_Chunk(World& world, Map& map,
                       const Position& position,
                       const World_Settings& settings,
                       World_File& worldFile);

            Full_Chunk              (const Full_Chunk& other) = delete;
            Full_Chunk& operator=   (const Full_Chunk& other) = delete;

            Full_Chunk              (Full_Chunk&& other) = default;
            Full_Chunk& operator=   (Full_Chunk&& other) = default;

            void tick();

            void   setBlock(const Block::Position& position, CBlock block);
            CBlock getBlock(const Block::Position& position) const;
            void   qSetBlock(const Block::Position& position, CBlock block);
            CBlock qGetBlock(const Block::Position& position) const;

            void    setBlock    (int x, int y, int z, CBlock block) override;
            void    qSetBlock   (int x, int y, int z, CBlock block) override;
            CBlock  qGetBlock   (int x, int y, int z) const override;
            CBlock  getBlock    (int x, int y, int z) const override;

            const Position& getPosition() const;

            const   Section* getSection     (int32_t index) const;
                    Section* editableGetSection (int32_t index);

            uint32_t draw   (Renderer::Master& renderer, const Camera& camera);
            bool tryGen     ();

            void addSection();

            uint32_t getHeightAt(int8_t x, int8_t z) const;
            const World& getWorld() const;

            void updateTopBlockLocation(const Block::Position& position);

            void setForDelete();
            bool hasDeleteFlag() const;

        private:
            void addSections(uint32_t blockTarget);
            void initBasicSunlight();
            bool overrideBlockFails(bool overrideBlocks,
                                    const Block::Position& position);

            Array2D<uint32_t, CHUNK_SIZE> m_highestBlocks;

            std::vector<Section>   m_chunkSections;

            Position    m_position;
            int32_t     m_sectionCount      = 0;
            int32_t     m_maxBlockHeight    = 0;

            World*      m_pWorld        = nullptr;
            Map*        m_pChunkMap     = nullptr;

            bool m_hasDeleteFlag = false;
    };
}

#endif // CFULL_CHUNK_H_INCLUDED

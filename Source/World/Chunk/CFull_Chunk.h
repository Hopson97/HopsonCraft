#ifndef CFULL_CHUNK_H_INCLUDED
#define CFULL_CHUNK_H_INCLUDED

#include <vector>
#include <memory>

#include "CBlock.h"
#include "CPosition.h"
#include "CSection.h"

#include "../../Util/Array2D.h"

namespace Renderer
{
    class Master;
}

class World;
class Camera;
class World_Settings;

namespace Chunk
{
    class Map;

    class Full_Chunk
    {
        public:
            Full_Chunk() = default;
            Full_Chunk(World& world, Map& map, const Position& position, const World_Settings& settings, bool generate = true);

            void generateBlocks(const World_Settings& settings);

            void   setBlock(const Block::Position& position, CBlock block, bool overrideBlocks = true);
            CBlock getBlock(const Block::Position& position);

            void   qSetBlock(const Block::Position& position, CBlock block, bool overrideBlocks = true);
            CBlock qGetBlock(const Block::Position& position);

            const Position& getPosition() const;
            Section* getSection(int32_t index);

            uint32_t draw   (Renderer::Master& renderer, const Camera& camera);
            bool tryGen (const Camera& camera);

            void addSection();

            uint32_t getHeightAt(int8_t x, int8_t z) const;

        private:
            void addSections(uint32_t blockTarget);
            void initBasicSunlight();
            void updateTopBlockLocation(const Block::Position& position);
            bool overrideBlockFails(bool overrideBlocks,
                                    const Block::Position& position);

            Array2D<uint32_t, CHUNK_SIZE> m_highestBlocks;

            std::vector<std::unique_ptr<Section>>   m_chunkSections;

            World*      mp_world        = nullptr;
            Map*        mp_chunkMap     = nullptr;
            Position    m_position;
            int32_t     m_sectionCount  = 0;
    };
}

#endif // CFULL_CHUNK_H_INCLUDED

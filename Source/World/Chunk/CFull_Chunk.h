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
    enum class State
    {
        New,
        Populating,
        Populated,
    };


    class Map;

    class Full_Chunk
    {
        public:
            Full_Chunk() = default;
            Full_Chunk(World& world, Map& map, const Position& position, const World_Settings& settings, bool generate = true);

            void generateBlocks(const World_Settings& settings);

            void   setBlock(const Block::Position& position, CBlock block);
            CBlock getBlock(const Block::Position& position);

            void   qSetBlock(const Block::Position& position, CBlock block, bool overrideBlocks = true);
            CBlock qGetBlock(const Block::Position& position);
            const Position& getPosition() const;

            ///@TODO Move to .cpp file
            State getState() { return m_state; }

            Section* getSection(int32_t index);

            uint32_t draw   (Renderer::Master& renderer, const Camera& camera);
            bool tryGen (const Camera& camera);

            void addSection();

            uint32_t getHeightAt(int8_t x, int8_t z) const;

        private:
            Array2D<uint32_t, CHUNK_SIZE> m_highestBlocks;


            std::vector<std::unique_ptr<Section>>   m_chunkSections;

            std::vector<CPositioned_Block> m_positionedBlocks;

            World*      mp_world        = nullptr;
            Map*        mp_chunkMap     = nullptr;
            Position    m_position;
            int32_t     m_sectionCount  = 0;

            State m_state = State::New;
    };
}

#endif // CFULL_CHUNK_H_INCLUDED

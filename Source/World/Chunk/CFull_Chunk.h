#ifndef CFULL_CHUNK_H_INCLUDED
#define CFULL_CHUNK_H_INCLUDED

#include <vector>
#include <memory>

#include "CBlock.h"
#include "CPosition.h"
#include "CSection.h"

namespace Renderer
{
    class Master;
}

class World;
class Camera;

namespace Chunk
{
    class Map;

    class Full_Chunk
    {
        public:
            Full_Chunk(World& world, Map& map, const Position& position);

            void   setBlock(const Block::Position& position, CBlock block, bool updateChunk = false);
            CBlock getBlock(const Block::Position& position);
            const Position& getPosition() const;



            Section* getSection(int32_t index);

            uint32_t draw   (Renderer::Master& renderer, const Camera& camera);
            bool tryGen (const Camera& camera);

            void addSection();

        private:
            std::vector<std::unique_ptr<Section>> m_chunkSections;

            World*      mp_world        = nullptr;
            Map*        mp_chunkMap     = nullptr;
            Position    m_position;
            int32_t     m_sectionCount  = 0;
    };
}

#endif // CFULL_CHUNK_H_INCLUDED

#ifndef CCOLUMN_H_INCLUDED
#define CCOLUMN_H_INCLUDED

#include <vector>
#include <memory>
#include <cstdint>

#include "Chunklet.h"
#include "CBlock.h"
#include "../Block/Block_Position.h"

namespace Renderer
{
    class Master;
}

namespace Chunk
{
    class Map;

    class Column
    {
        struct CFlags
        {
            CFlags()
            :   hasFullMesh (false)
            ,   hasBuffered (false) {}

            std::atomic<bool> hasFullMesh;
            std::atomic<bool> hasBuffered;
        };


        public:
            Column(const Position& pos, Map& map);

            void createFullMesh();

            void draw(Renderer::Master& renderer);
            const Position& getPosition() const;
            void setBlock(const Block::Column_Position& pos, CBlock block);

            const Chunklet* getChunklet(int32_t index) const;

            const CFlags& getFlags() { return m_flags; }

        private:
            void addChunklet();

            std::vector<std::unique_ptr<Chunklet>> m_chunklets;

            Position m_position;
            Map* m_p_chunkMap = nullptr;

            int32_t m_chunkCount = 0;

            CFlags m_flags;
    };
}

#endif // CCOLUMN_H_INCLUDED

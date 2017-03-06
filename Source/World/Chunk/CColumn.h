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
            ,   hasBuffered (false)
            ,   deleteMe    (false)
            ,   generated   (false) {}

            std::atomic<bool> hasFullMesh;
            std::atomic<bool> hasBuffered;
            std::atomic<bool> deleteMe;
            std::atomic<bool> generated;
        };


        public:
            Column(const Position& pos, Map& map);

            void createFullMesh();

            void update();
            void draw(Renderer::Master& renderer);
            const Position& getPosition() const;

            void    setBlock    (const Block::Column_Position& pos, CBlock block);
            CBlock  getBlock    (const Block::Column_Position& pos) const;

            Chunklet* getChunklet(int32_t index);

            const CFlags& getFlags();
            void setDeleteFlag(bool deleteF);

        private:
            Chunklet* getChunkletnc(int32_t index);
            void addChunklet();

            std::vector<Chunklet*> m_chunkletsToUpdate;
            std::vector<std::unique_ptr<Chunklet>> m_chunklets;

            Position m_position;
            Map* m_p_chunkMap = nullptr;

            int32_t m_chunkCount = 0;

            CFlags m_flags;
    };
}

#endif // CCOLUMN_H_INCLUDED

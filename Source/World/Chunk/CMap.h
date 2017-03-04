#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <memory>

#include "CColumn.h"
#include "CPosition.h"



namespace Renderer
{
    class Master;
}

namespace Chunk
{
    class Map
    {
        public:
            Map();

            void update();
            void draw(Renderer::Master& renderer);

            void addChunk(const Position& pos);
            const Column* getChunklet(const Chunk::Position& pos) const;
            Column* getChunklet(const Chunk::Position& pos);

        private:
            std::unordered_map<Chunk::Position, std::unique_ptr<Column>> m_chunks;
    };
}

#endif // CMAP_H_INCLUDED

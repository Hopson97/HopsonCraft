#ifndef CCOLUMN_H_INCLUDED
#define CCOLUMN_H_INCLUDED

#include <stack>
#include <memory>

#include "Chunklet.h"

namespace Renderer
{
    class Master;
}

namespace Chunk
{
    class Map;

    class Column
    {
        public:
            Column(const Position& pos, Map& map);

            void draw(Renderer::Master& renderer);

            const Position& getPosition() const;

        private:
            std::vector<std::unique_ptr<Chunklet>> m_chunklets;

            Position m_position;
            Map* m_p_chunkMap = nullptr;

            uint32_t m_chunkCount = 0;
    };
}

#endif // CCOLUMN_H_INCLUDED

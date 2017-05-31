#include "StructuresBuilder.h"

#include "../IBlock_Accessible.h"

namespace Structure
{
    void Builder::addBlock(const Defer_Block& block)
    {
        m_deferBlocks.push_back(std::move(block));
    }

    void Builder::build(IBlock_Accessible& access)
    {
        for (auto& block : m_deferBlocks)
        {
            int64_t x = block.pos.x;
            int64_t y = block.pos.y;
            int64_t z = block.pos.z;
            access.setBlock(x, y, z, block.block);
        }
    }

    void Builder::fillXZ(const Block::Position& start,
                                   const Block::Position& finish,
                                   CBlock fill)
    {
        for (int64_t x = start.x; x <= finish.x; x++)
        for (int64_t z = start.z; z <= finish.z; z++)
        {
            int64_t y = start.y;
            m_deferBlocks.emplace_back(x, y, z, fill);
        }
    }

    void Builder::makeColumn(const Block::Position& base, int64_t height, CBlock block)
    {
        for (int32_t y = base.y + 1; y < base.y + height; y++)
        {
            m_deferBlocks.emplace_back(base.x, y, base.z, block);
        }
    }
}

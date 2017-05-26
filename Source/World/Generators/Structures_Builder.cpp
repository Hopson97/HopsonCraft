#include "Structures_Builder.h"

#include "../IBlock_Accessible.h"

void Structure_Builder::addBlock(const Defer_Block& block)
{
    m_deferBlocks.push_back(std::move(block));
}

void Structure_Builder::build(IBlock_Accessible& access)
{
    for (auto& block : m_deferBlocks)
    {
        int x = block.pos.x;
        int y = block.pos.y;
        int z = block.pos.z;
        access.setBlock(x, y, z, block.block);
    }
}

void Structure_Builder::fillXZ(const Block::Position& start,
                               const Block::Position& finish,
                               CBlock fill)
{
    for (int x = start.x; x <= finish.x; x++)
    for (int z = start.z; z <= finish.z; z++)
    {
        int y = start.y;
        m_deferBlocks.emplace_back(x, y, z, fill);
    }
}

void Structure_Builder::makeColumn(const Block::Position& base, int height, CBlock block)
{
    for (int32_t y = base.y + 1; y < base.y + height; y++)
    {
        m_deferBlocks.emplace_back(base.x, y, base.z, block);
    }
}


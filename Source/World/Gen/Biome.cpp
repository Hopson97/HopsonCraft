#include "Biome.h"

#include "../../Util/Random.h"


void Biome::setDepth(int depth)
{
    m_depth = depth;
}

void Biome::addBlock(const Block_t& block, int frequency)
{
    m_blocks.emplace_back(block, frequency);
    m_totalFrequency += frequency;
}

const Block_t& Biome::getBlock() const
{
    /* to do, add chances */
    return *m_blocks.at(0).block;
}

int Biome::getDepth() const
{
    return m_depth;
}

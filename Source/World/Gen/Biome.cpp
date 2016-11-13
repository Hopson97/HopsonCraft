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

void Biome::addTree(Structure_Function function)
{
    m_treeCreators.push_back(function);
}

Structure_Function Biome::getTreeFunction()
{
    return m_treeCreators.at(0);
}




int Biome::getDepth() const
{
    return m_depth;
}

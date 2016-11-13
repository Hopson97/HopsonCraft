#include "Biome.h"

#include "../../Util/Random.h"


void Biome::setDepth(int depth)
{
    m_depth = depth;
}

void Biome::setTreeFrequency(int frequency)
{
    m_treeFrequency = frequency;
}

void Biome::addBlock(const Block_t& block, int frequency)
{
    m_blocks.emplace_back(block, frequency);
    m_totalFrequency += frequency;
}

const Block_t& Biome::getBlock() const
{
    auto i = Random::integer(0, m_blocks.size() - 1);
    return *m_blocks.at(i).block;
}

void Biome::addTree(Structure_Function function)
{
    m_treeCreators.push_back(function);
}

Structure_Function Biome::getTreeFunction()
{
    auto i = Random::integer(0, m_treeCreators.size() - 1);
    return m_treeCreators.at(i);
}

int Biome::getDepth() const
{
    return m_depth;
}

int Biome::getTreeFrequency() const
{
    return m_treeFrequency;
}


void Biome::addFlora(const Block_t& block)
{
    m_flora.push_back(&block);
}

const Block_t& Biome::getFlora() const
{
    auto i = Random::integer(0, m_flora.size() - 1);
    return *m_flora.at(i);
}

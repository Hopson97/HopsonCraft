#include "Biome.h"

using RNG = Random::Generator<std::minstd_rand>;

Biome::Biome(std::string&& fileName)
{

}

CBlock Biome::getSurfaceBlock(RNG& rd)
{
    return getBlock(m_surfaceBlocks, rd);
}

CBlock Biome::getFloraBlock(RNG& rd)
{
    return getBlock(m_floraBlocks, rd);
}

Structure_ID Biome::getTree(RNG& rd)
{
    int total = m_trees.total;
    return m_trees.holder[rd.intInRange(0, total)];
}

CBlock Biome::getBlock(const Biome::Gen_Container<CBlock>& container, RNG rd)
{
    int total = container.total;
    return container.holder[rd.intInRange(0, total)];
}

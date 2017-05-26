#include "Biome.h"

#include "../../Util/STD_Util.h"

Biome::Biome(std::string&& fileName, const std::string& worldGen)
:   m_fileName      (std::move(fileName))
,   m_worldGenName  (worldGen)
{
    std::string fullName = "Data/WorldGen/" + m_worldGenName + "/" + m_fileName + ".biome";
    Loader::load(fullName);
}

CBlock Biome::getSurfaceBlock(RNG& rd) const
{
    return getBlock(m_surfaceBlocks, rd);
}

CBlock Biome::getFloraBlock(RNG& rd) const
{
    return getBlock(m_floraBlocks, rd);
}

bool Biome::hasFlora() const
{
    return m_floraBlocks.total > 0;
}

bool Biome::hasStructure() const
{
    return m_trees.total > 0;
}

int Biome::getFloraFrequency() const
{
    return m_floraFreq;
}

int Biome::getTreeFrequencey() const
{
    return m_treeFreq;
}



Structure::ID Biome::getTree(RNG& rd) const
{
    return m_trees.holder[rd.intInRange(0, m_trees.total - 1)];
}

CBlock Biome::getBlock(const Biome::Gen_Container<CBlock>& container, RNG& rd) const
{
    return container.holder[rd.intInRange(0, container.total - 1)];
}

const Noise::Data& Biome::getNoise() const
{
    return m_noise;
}

bool Biome::parseLine(const std::string& line, std::ifstream& inFile)
{
    if (areStringsSame(line, "Noise"))
    {
        loadNoise(inFile);
    }
    else if (areStringsSame(line, "Surface"))
    {
        loadIntoBlockList(inFile, m_surfaceBlocks);
    }
    else if (areStringsSame(line, "Flora"))
    {
        loadIntoBlockList(inFile, m_floraBlocks);
    }
    else if (areStringsSame(line, "Tree"))
    {
        loadTree(inFile);
    }
    else if (areStringsSame(line, "Flora Freq"))
    {
        inFile >> m_floraFreq;
    }
    else if (areStringsSame(line, "Tree Freq"))
    {
        inFile >> m_treeFreq;
    }
    else
    {
        return false;
    }
    return true;
}

void Biome::loadNoise(std::ifstream& inFile)
{
    int octaves,
        amplitude,
        heightOffset;

    float   roughness,
            smoothness;


    inFile >> octaves >> amplitude >> roughness >> smoothness >> heightOffset;

    m_noise = {octaves, amplitude, roughness, smoothness, heightOffset};
}

void Biome::loadTree(std::ifstream& inFile)
{
    int id, freq;
    inFile >> id >> freq;

    auto idEnum = (Structure::ID)id;

    for (int i = 0; i <freq; i++)
    {
        m_trees.holder.push_back(idEnum);
    }
    m_trees.total += freq;
}

void Biome::loadIntoBlockList(std::ifstream& inFile,
                              Gen_Container<CBlock>& container)
{
    int id, freq;
    inFile >> id >> freq;

    for (int i = 0; i < freq; i++)
    {
        container.holder.emplace_back(id);
    }
    container.total += freq;
}









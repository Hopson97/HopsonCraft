#include "Generation_Type.h"

#include "../../Util/STD_Util.h"
#include "../../Maths/General_Maths.h"

bool World_Generation_Type::BiomeRange::isThisBiome(int biomeKey)
{
    switch (m_compare)
    {
        case Compare::Greater:
            return biomeKey >= m_max;

        case Compare::Less:
            return biomeKey <= m_max;

        case Compare::Range:
            return Maths::inRange(biomeKey, m_min, m_max);
    }
    return false;
}

const Biome& World_Generation_Type::BiomeRange::getBiome() const
{
    return m_biome;
}





World_Generation_Type::World_Generation_Type(const std::string& folderName)
:   m_folder    (folderName)
{
    std::string full = "Data/WorldGen/" + m_folder + "/Info.biome";
    Loader::load(full);
}

const Noise::Data& World_Generation_Type::getBiomeMapNoise()
{
    return m_biomeNoise;
}

const Biome& World_Generation_Type::getBiome(int biomeKey)
{
    for (auto& biome : m_biomes)
    {
        if (biome.isThisBiome(biomeKey))
        {
            return biome.getBiome();
        }
    }
    throw std::runtime_error("Unable to get biome: " + std::to_string(biomeKey));
    ///@TODO Return an "error biome" rather than crash the game
}




bool World_Generation_Type::parseLine(const std::string& line, std::ifstream& inFile)
{
    if (areStringsSame(line, "Noise"))
    {
        loadNoise(inFile);
    }
    else if (areStringsSame(line, "Biome"))
    {
        loadBiome(inFile);
    }
    else
    {
        return false;
    }
    return true;
}

void World_Generation_Type::loadNoise(std::ifstream& inFile)
{
    int octaves,
        amplitude,
        heightOffset;

    float   roughness,
            smoothness;


    inFile >> octaves >> amplitude >> roughness >> smoothness >> heightOffset;

    m_biomeNoise = {octaves, amplitude, roughness, smoothness, heightOffset};
}

void World_Generation_Type::loadBiome(std::ifstream& inFile)
{
    std::string compareString;
    std::string biomeName;

    Compare compare;
    int     minVal = 0;
    int     maxVal = 0;

    std::getline(inFile, biomeName);
    std::getline(inFile, compareString);

    if (areStringsSame(compareString, "Range"))
    {
        compare = Compare::Range;
    }
    else if (areStringsSame(compareString, "Greater"))
    {
        compare = Compare::Greater;
    }
    else if (areStringsSame(compareString, "Less"))
    {
        compare = Compare::Less;
    }
    else
    {
        throw std::runtime_error("Token: " + compareString + " not known.");
    }

    switch (compare)
    {
        case Compare::Greater:
        case Compare::Less:
            inFile >> maxVal;
            break;

        case Compare::Range:
            inFile >> minVal >> maxVal;
            break;
    }

    Biome b(std::move(biomeName), m_folder);

    m_biomes.emplace_back(minVal, maxVal, compare, std::move(b));
}




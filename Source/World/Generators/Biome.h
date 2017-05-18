#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include <fstream>

#include "G_ID.h"
#include "../Chunk/CNodes.h"
#include "../../Util/Random.h"

#include "../../Temp/Noise_Generator.h"

class Biome
{
    using RNG = Random::Generator<std::minstd_rand>;

    struct Range
    {
        int minVal;
        int maxVal;
    };

    template<typename T>
    struct Gen_Container
    {
        std::vector<T>  holder;
        int             total;
    };

    public:
        Biome(std::string&& fileName, const std::string& worldGen);

        CBlock          getSurfaceBlock (RNG& rd);
        CBlock          getFloraBlock   (RNG& rd);
        Structure_ID    getTree         (RNG& rd);

        const Noise::Data& getNoise     () const;

    private:
        void load();
        void parseLine  (const std::string& line, std::ifstream& inFile);
        void loadNoise  (std::ifstream& inFile);
        void loadTree   (std::ifstream& inFile);

        void loadIntoBlockList(std::ifstream& inFile, Gen_Container<CBlock>& container);

        CBlock getBlock(const Biome::Gen_Container<CBlock>& container, RNG rd);

        std::string m_fileName;
        std::string m_worldGenName;

        Noise::Data             m_noise;

        Gen_Container<CBlock>   m_surfaceBlocks;
        Gen_Container<CBlock>   m_floraBlocks;

        Gen_Container<Structure_ID> m_trees;
};




#endif // BIOME_H_INCLUDED

#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include <fstream>

#include "../Chunk/Nodes.h"
#include "../../Util/Random.h"
#include "../../Util/Loader.h"
#include "../../Temp/Noise_Generator.h"

#include "Structures.h"

typedef Random::Generator<std::mt19937> RNG;

class Biome : public Loader
{
    struct Range
    {
        int minVal;
        int maxVal;
    };

    template<typename T>
    struct Gen_Container
    {
        std::vector<T>  holder;
        int             total = 0;
    };

    public:
        Biome(std::string&& fileName, const std::string& worldGen);

        CBlock          getSurfaceBlock (RNG& rd) const;
        CBlock          getFloraBlock   (RNG& rd) const;
        Structure::ID   getTree         (RNG& rd) const;

        bool hasFlora       () const;
        bool hasStructure   () const;

        int getFloraFrequency() const;
        int getTreeFrequencey() const;


        const Noise::Data& getNoise     () const;

    private:
        bool parseLine  (const std::string& line, std::ifstream& inFile);
        void loadNoise  (std::ifstream& inFile);
        void loadTree   (std::ifstream& inFile);

        void loadIntoBlockList(std::ifstream& inFile, Gen_Container<CBlock>& container);

        CBlock getBlock(const Biome::Gen_Container<CBlock>& container, RNG& rd) const;

        std::string m_fileName;
        std::string m_worldGenName;

        Noise::Data             m_noise;

        Gen_Container<CBlock>   m_surfaceBlocks;
        Gen_Container<CBlock>   m_floraBlocks;

        Gen_Container<Structure::ID> m_trees;

        int m_floraFreq     = 0;
        int m_treeFreq      = 0;
};




#endif // BIOME_H_INCLUDED

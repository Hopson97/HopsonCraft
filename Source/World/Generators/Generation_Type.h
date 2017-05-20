#ifndef GENERATION_TYPE_H_INCLUDED
#define GENERATION_TYPE_H_INCLUDED

#include "Biome.h"

#include "../../Util/Loader.h"

///@TODO Come up with a better name for this class
class World_Generation_Type : public Loader
{
    enum class Compare
    {
        Greater = 0,
        Range   = 1,
        Less    = 2
    };

    ///@TODO Come up with a better name for this class
    class BiomeRange
    {
        public:
            BiomeRange(int min, int max, Compare c, Biome&& b)
            :   m_biome     (std::move(b))
            ,   m_min       (min)
            ,   m_max       (max)
            ,   m_compare   (c)
            { }

            bool isThisBiome(int biomeKey);

            const Biome& getBiome() const;

        private:
            Biome   m_biome;
            int     m_min, m_max;
            Compare m_compare;
    };

    public:
        World_Generation_Type(const std::string& folderName);

        const Noise::Data&  getBiomeMapNoise    ();
        const Biome&        getBiome            (int biomeKey);

    private:
        bool parseLine  (const std::string& line, std::ifstream& inFile);
        void loadNoise  (std::ifstream& inFile);
        void loadBiome  (std::ifstream& inFile);

        std::vector<BiomeRange> m_biomes;

        Noise::Data m_biomeNoise;

        std::string m_folder;
};


#endif // GENERATION_TYPE_H_INCLUDED

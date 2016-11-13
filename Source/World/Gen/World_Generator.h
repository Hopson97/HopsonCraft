#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <vector>

#include "../Block/Block.h"
#include "Biome.h"
#include "Structure.h"
#include "../../Util/Noise_Generator.h"

namespace Noise_Generator
{
    struct Data;
}

class Chunk;
class Block_Location;

class World_Generator
{
    public:
        World_Generator(Chunk& chunk);

        void generate();

    private:
        void generateHeightMap  ();
        void generateBiomeMap   ();
        void generateMap        (std::vector<int>& valueMap, const Noise::Generator& noiseGenerator);

        void generateBlockData  ();

        void setRandomSeed      (char x, int y, char z);

        void setBlock           (const Block_Location& location, int h);
        void setBlock           (const Block_Location& location, const Block_t& block);

        void tryAddTree         (const Block_Location& location);

        void setActiveBiome     (int value);
        void setUpBiomes        ();


        Chunk* m_p_chunk;

        std::vector<int> m_heightMap;
        std::vector<int> m_biomeMap;

        int m_maxHeight;
        int terrainSeed;

        Biome* m_p_activeBiome;
        Biome m_forestBiome;
        Biome m_desertBiome;
        Biome m_snowBiome;

        Noise::Generator m_terrainNoise;
        Noise::Generator m_biomeNoise;


};

#endif // WORLD_GENERATOR_H

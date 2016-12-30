#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <vector>
#include <unordered_map>
#include <cstdint>

#include "../Block/Block_Type/Block_Type.h"
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
        World_Generator(Chunk& chunk,
                        uint32_t seed);

        void generate();

    private:
        void generateHeightMap  ();
        void generateBiomeMap   ();
        void generateMap        (std::vector<int>& valueMap, const Noise::Generator& noiseGenerator);

        void generateBlockData  ();

        void setRandomSeed      (int x, int y, int z);

        void setBlock           (const Block_Location& location, int h);
        void setBlock           (const Block_Location& location, const Block::Block_Type& block);

        void tryAddTree         (const Block_Location& location);
        void tryAddFlora        (const Block_Location& location);

        void setActiveBiome     (int value);

        void setUpBiomes ();

        Chunk* m_p_chunk;

        std::vector<int> m_heightMap;
        std::vector<int> m_biomeMap;

        std::unordered_map<Block_Location, Structure_Function>          m_structures;
        std::unordered_map<Block_Location, const Block::Block_Type*>    m_flora;

        int m_maxHeight;
        uint32_t m_seed;

        Biome* m_p_activeBiome;
};

#endif // WORLD_GENERATOR_H

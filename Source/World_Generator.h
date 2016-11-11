#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <vector>

#include "Biome.h"

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
        void generateMap        ();

        void setRandomSeed      (char x, int y, char z);

        void setBlock           (const Block_Location& location, int h);
        void setBlock           (const Block_Location& location, const Block_t& block);

        Chunk* m_p_chunk;

        std::vector<int> m_heightMap;
        std::vector<int> m_biomeMap;

        int m_maxHeight;
};

#endif // WORLD_GENERATOR_H

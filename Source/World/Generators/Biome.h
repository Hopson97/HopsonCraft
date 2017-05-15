#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include "../Chunk/CNodes.h"

#include "../../Util/Random.h"

class Biome
{
    using RNG = Random::Generator<std::minstd_rand>;

    struct Block
    {
        CBlock Block;
        int chance;
    }

    struct Structure
    {
        Structure_ID id;
        int chance;
    };

    template<typename T>
    struct Gen_Container
    {
        std::vector<T>  container;
        int             total;
    };

    public:
        Biome(std::string&& fileName);

        void getSurfaceBlock(Random::Generator<std::minstd_rand> rd});

    private:
        Gen_Container<Block>        m_surfaceBlocks;
        Gen_Container<Block>        m_floraBlocks;

        Gen_Container<Structure>    m_trees;
};

#endif // BIOME_H_INCLUDED

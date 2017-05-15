#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include "../Chunk/CNodes.h"
#include "G_ID.h"
#include "../../Util/Random.h"

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
        Biome(std::string&& fileName);

        CBlock          getSurfaceBlock(RNG& rd);
        CBlock          getFloraBlock  (RNG& rd);
        Structure_ID    getTree        (RNG& rd);

    private:
        CBlock getBlock(const Biome::Gen_Container<CBlock>& container, RNG rd);

        Gen_Container<CBlock>   m_surfaceBlocks;
        Gen_Container<CBlock>   m_floraBlocks;

        Gen_Container<Structure_ID> m_trees;
};

#endif // BIOME_H_INCLUDED

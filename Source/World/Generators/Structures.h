#ifndef GSTRUCTURES_H_INCLUDED
#define GSTRUCTURES_H_INCLUDED

#include "Buildings.h"
#include "Trees.h"

namespace Structure
{
    enum class ID
    {
        Oak_Tree        = 0,
        Acacia_Tree     = 1,
        Palm_Tree       = 2,

        Pyramid         = 100,
    };

    void createFromID(ID id,
                      IBlock_Accessible& access,
                      const Block::Position& pos,
                      Random::Generator<std::mt19937>& random);
}

#endif // GSTRUCTURES_H_INCLUDED




















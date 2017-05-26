#ifndef G_ID_H_INCLUDED
#define G_ID_H_INCLUDED

#include "Trees.h"
#include "Structures.h"

enum class Structure_ID
{
    Oak_Tree        = 0,
    Acacia_Tree     = 1,
    Palm_Tree       = 2,

    Pyramid         = 100,
};

void getStructureFromID(IBlock_Accessible& access,
                        const Block::Position& pos,
                        Random::Generator<std::mt19937>& random,
                        Structure_ID id);

#endif // G_ID_H_INCLUDED

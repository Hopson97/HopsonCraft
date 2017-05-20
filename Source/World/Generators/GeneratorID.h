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

template<typename Access, typename Rand>
void getStructureFromID(Access& access,
                        const Block::Position& pos,
                        Random::Generator<Rand> random,
                        Structure_ID id)
{
    switch (id)
    {
        case Structure_ID::Oak_Tree:
            makeOakTree(access, pos, random);
            break;

        case Structure_ID::Acacia_Tree:
            makeAcaciaTree(access, pos, random);
            break;

        case Structure_ID::Palm_Tree:
            makePalmTree(access, pos, random);
            break;


        case Structure_ID::Pyramid:
            makePyramid(access, pos);
            break;
    }
}

#endif // G_ID_H_INCLUDED

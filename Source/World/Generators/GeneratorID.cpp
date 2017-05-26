#include "GeneratorID.h"

void getStructureFromID(IBlock_Accessible& access, const Block::Position& pos, Random::Generator<std::mt19937>& random, Structure_ID id)
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
            makePyramid(access, pos, random);
            break;
    }
}

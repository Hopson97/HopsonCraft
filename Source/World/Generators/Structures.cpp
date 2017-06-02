#include "Structures.h"

namespace Structure
{
    void createFromID(  ID id,
                        IBlock_Accessible& access,
                        const Block::Position& pos,
                        Random::Generator<std::mt19937>& random)
    {
        switch(id)
        {
            case ID::Oak_Tree:
                makeOakTree(access, pos, random);
                break;

            case ID::Acacia_Tree:
                makeAcaciaTree(access, pos, random);
                break;

            case ID::Palm_Tree:
                makePalmTree(access, pos, random);
                break;


            case ID::Pyramid:
                makePyramid(access, pos, random);
                break;
        }
    }

}

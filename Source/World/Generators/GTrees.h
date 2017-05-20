#ifndef GTREES_H_INCLUDED
#define GTREES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

//See GStructures.h for a definition of the args

///@TODO Refactor the sh*t out of this

class IBlock_Accessible;

void makeOakTree(IBlock_Accessible& access,
                 const Block::Position& pos,
                 Random::Generator<std::mt19937>& random);

void makePalmTree(IBlock_Accessible& access,
                  const Block::Position& pos,
                  Random::Generator<std::mt19937>& random);

template<typename Access, typename Rand>
void makeAcaciaTree(Access& access,
                 const Block::Position& pos,
                 Random::Generator<Rand> random,
                 bool isMadeDuringWorldGen = true)
{/*
    auto height = random.intInRange(5, 8);
    auto width1 = random.intInRange(4, 5);
    auto dir1 = random.intInRange(0, 1);

    for (int32_t y = 1; y < height; y++)
    {
        access.qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
    }

    float y = pos.y + height;
    switch(dir1)
    {
        case 0:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x, (int)std::floor(y), pos.z + i}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;

        case 1:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x + i, (int)std::floor(y), pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;
    }

    auto dir2 = random.intInRange(0, 1);

    for (int32_t y = 1; y < height; y++)
    {
        access.qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
    }

    y = pos.y + height;
    switch(dir2)
    {
        case 0:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x, (int)std::floor(y), pos.z - i}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;

        case 1:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x - i, (int)std::floor(y), pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;
    }
*/
    ///@TODO Leaves for the Acacia tree
}

#endif // GTREES_H_INCLUDED

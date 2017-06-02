#ifndef GTREES_H_INCLUDED
#define GTREES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"


class IBlock_Accessible;

namespace Structure
{

void makeOakTree(IBlock_Accessible& access,
                 const Block::Position& pos,
                 Random::Generator<std::mt19937>& random);

void makePalmTree(IBlock_Accessible& access,
                  const Block::Position& pos,
                  Random::Generator<std::mt19937>& random);

void makeAcaciaTree(IBlock_Accessible& access,
                    const Block::Position& pos,
                    Random::Generator<std::mt19937>& random);

}

#endif // GTREES_H_INCLUDED

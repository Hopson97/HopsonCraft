#ifndef BUILDINGS_H_INCLUDED
#define BUILDINGS_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

class IBlock_Accessible;

namespace Structure
{
    void makePyramid(IBlock_Accessible& access,
                      const Block::Position& pos,
                      Random::Generator<std::mt19937>& random);

}

#endif // BUILDINGS_H_INCLUDED

#ifndef GSTRUCTURES_H_INCLUDED
#define GSTRUCTURES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

class IBlock_Accessible;

void makePyramid(IBlock_Accessible& access,
                  const Block::Position& pos,
                  Random::Generator<std::mt19937>& random);

#endif // GSTRUCTURES_H_INCLUDED




















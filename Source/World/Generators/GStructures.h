#ifndef GSTRUCTURES_H_INCLUDED
#define GSTRUCTURES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"

/*
    Q: What is the template "Access"?

    A: Access is the way this function is able to reach functions such as "setBlock" and "qSetBlock",
    as this can be done in multiple areas.

    For example, if you make a tree during generation, then it just uses a "Full_Chunk"

    But, if a tree is grown from a sapling (As of 30/04/2017, this is not in the game), then it
    uses the "world" to access these functions.

    The reason being is that the world set blocks functions will add a changed chunk into a chunk
    rebuild std::vector, which is very handy!
*/

template<typename Access>
void makePyramid(Access& access,
                 const Block::Position& pos)
{
    for (int base = 9, h = 0; base > 0; base -= 2, h++)
    for (int x = pos.x - base / 2; x < pos.x + base / 2; x++)
    for (int z = pos.z - base / 2; z < pos.z + base / 2; z++)
    {
        access.setBlock({pos.x + x, pos.y + h + 1, pos.z + z}, Block::ID::Stone);
    }
}

#endif // GSTRUCTURES_H_INCLUDED

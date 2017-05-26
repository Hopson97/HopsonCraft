#include "Buildings.h"

#include "../Chunk/Nodes.h"
#include "../IBlock_Accessible.h"

#include "Structures_Builder.h"

namespace Structure
{
    void makePyramid(IBlock_Accessible& access,
                     const Block::Position& pos,
                     Random::Generator<std::mt19937>& random)
    {


        for (int base = 9, h = 0; base > 0; base -= 2, h++)
        for (int x = pos.x - base / 2; x < pos.x + base / 2; x++)
        for (int z = pos.z - base / 2; z < pos.z + base / 2; z++)
        {
            access.setBlock(pos.x + x, pos.y + h + 1, pos.z + z, Block::ID::Stone);
        }
    }
}

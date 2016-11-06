#include "D_Blocks.h"

#include <map>

namespace Block
{
    Block::Block_Base air       ("Air");
    Block::Block_Base grass     ("Grass");
    Block::Block_Base dirt      ("Dirt");
    Block::Block_Base stone     ("Stone");
    Block::Block_Base water     ("Water");
    Block::Block_Base sand      ("Sand");
    Block::Block_Base oakLeaf   ("Oak_Leaf");
    Block::Block_Base oakWood   ("Oak_Wood");
    Block::Block_Base oakPlank  ("Oak_Plank");
    Block::Block_Base glass     ("Glass");
    Block::Block_Base cobbleStone   ("Cobblestone");
    Block::Block_Base stoneBricks   ("Stone_Bricks");
    Block::Block_Base snowGrass     ("Snow_Grass");

    std::map<Block::ID, Block::Block_Base*> blockMap;

    void initBlockDatabase()
    {
        blockMap[Block::ID::Air]    = &air;
        blockMap[Block::ID::Grass]  = &grass;
        blockMap[Block::ID::Dirt]   = &dirt;
        blockMap[Block::ID::Stone]  = &stone;
        blockMap[Block::ID::Sand]   = &sand;
        blockMap[Block::ID::Water]  = &water;
        blockMap[Block::ID::Oak_Leaf]   = &oakLeaf;
        blockMap[Block::ID::Oak_Wood]   = &oakWood;
        blockMap[Block::ID::Oak_Plank]  = &oakPlank;
        blockMap[Block::ID::Glass]      = &glass;
        blockMap[Block::ID::Cobble_Stone]   = &cobbleStone;
        blockMap[Block::ID::Stone_Brick]    = &stoneBricks;
        blockMap[Block::ID::Snow_Grass]     = &snowGrass;
    }

    Block::Block_Base& getBlockFromId (Block::ID id)
    {
        return *blockMap.at(id);
    }
}

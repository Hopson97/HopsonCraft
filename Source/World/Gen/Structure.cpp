#include "Structure.h"

#include "../Block/Block_Location.h"
#include "../Chunk/Chunk.h"
#include "../Block/D_Blocks.h"

#include "../../Util/Random.h"

namespace Structure
{
    Structure_Function makeOak      (&createOak);
    Structure_Function makeCactus   (&createCactus);
    Structure_Function makeSpruce   (&createSpruce);

    void createOak(Chunk& chunk, const Block_Location& location, bool overwriteBlocks)
    {
        auto trunkHeight = Random::integer(5, 8);
        //Make the trunk
        for (auto i = 1 ; i < trunkHeight + 1 ; i++)
        {
            chunk.addBlock({location.x, location.y + i, location.z}, Block::oakWood, overwriteBlocks);
        }
        int y = trunkHeight + location.y;

        for (int xLeaf = location.x - 2 ; xLeaf < location.x + 3 ; xLeaf++)
        {
            for (int zLeaf = location.z - 2 ; zLeaf < location.z + 3 ; zLeaf++)
            {
                chunk.addBlock({xLeaf, y, zLeaf}, Block::oakLeaf, overwriteBlocks);
                chunk.addBlock({xLeaf, y + 1, zLeaf}, Block::oakLeaf, overwriteBlocks);
            }
        }
        y++;

        for (int xLeaf = location.x - 1 ; xLeaf < location.x + 2 ; xLeaf++)
        {
            for (int zLeaf = location.z - 1 ; zLeaf < location.z + 2 ; zLeaf++)
            {
                chunk.addBlock({xLeaf, y, zLeaf}, Block::oakLeaf, overwriteBlocks);
            }
        }
        y++;

        chunk.addBlock({location.x - 1, y,   location.z},       Block::oakLeaf, overwriteBlocks);
        chunk.addBlock({location.x + 1, y,   location.z},       Block::oakLeaf, overwriteBlocks);
        chunk.addBlock({location.x,     y,   location.z},       Block::oakLeaf, overwriteBlocks);
        chunk.addBlock({location.x,     y,   location.z + 1},   Block::oakLeaf, overwriteBlocks);
        chunk.addBlock({location.x,     y,   location.z - 1},   Block::oakLeaf, overwriteBlocks);
    }

    void createCactus(Chunk& chunk, const Block_Location& location, bool overwriteBlocks)
    {
        auto cactusHeight = Random::integer(5, 7);

        for (auto i = 1 ; i < cactusHeight + 1 ; i++)
        {
            chunk.addBlock({location.x, location.y + i, location.z}, Block::cactus, overwriteBlocks);
        }
    }

    void  createSpruce(Chunk& chunk, const Block_Location& location, bool overwriteBlocks)
    {/*
        auto trunkHeight = Random::integer(5, 8);
        //Make the trunk
        for (auto i = 1 ; i < trunkHeight + 1 ; i++)
        {
            chunk.addBlock({location.x, location.y + i, location.z}, Block::oakWood, overwriteBlocks);
        }
        int y = trunkHeight + location.y;*/
    }

}


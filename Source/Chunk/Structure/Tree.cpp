#include "Tree.h"

#include "Chunk.h"
#include "Chunk_Location.h"
#include "Random.h"
#include "D_Blocks.h"

namespace Tree
{
    void makeOakTree (Chunk& chunk, const Block_Location& location)
    {
        auto trunkHeight = Random::integer(5, 8);
        //Make the trunk
        for (auto i = 1 ; i < trunkHeight + 1 ; i++)
        {
            chunk.getBlocks().setBlock({location.x, location.y + i, location.z}, Block::oakWood, false);
        }

        //Make the crown
        for (auto yLeaf = location.y + trunkHeight ; yLeaf < location.y + trunkHeight + 4 ; yLeaf++)
        {
            for (auto xLeaf = location.x - 2 ; xLeaf < location.x + 3 ; xLeaf++)
            {
                for (auto zLeaf = location.z - 2 ; zLeaf < location.z + 3 ; zLeaf++)
                {
                    chunk.getBlocks().setBlock({xLeaf, yLeaf, zLeaf}, Block::oakLeaf, false );
                }
            }
        }
    }

    void makeCactus(Chunk& chunk, const Block_Location& location)
    {
        auto cactusHeight = Random::integer(5, 7);

        for (auto i = 1 ; i < cactusHeight + 1 ; i++)
        {
            chunk.getBlocks().setBlock({location.x, location.y + i, location.z}, Block::cactus, false);
        }
    }

}

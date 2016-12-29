#include "Grass.h"

#include "../../Chunk/Chunk.h"
#include "../Block_Location.h"

namespace Block
{
    Grass::Grass()
    :   Block_Type ("Grass")
    { }
/*
    Interaction_Type Grass::interact(Chunk& chunk, const Block_Location& location, Temp_Item_ID id) const
    {
        //chunk.addBlock(location, Block::get(Block::ID::Dirt), true);
        //return Interaction_Type::Chunk_Block_Change;
        return Interaction_Type::None;
    }
*/
}

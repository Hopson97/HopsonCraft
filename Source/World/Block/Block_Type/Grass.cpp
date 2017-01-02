#include "Grass.h"

#include "../../Chunk/Chunk.h"
#include "../Block_Location.h"

#include <iostream>

namespace Block
{
    Grass::Grass()
    :   Block_Type ("Grass")
    { }

    bool tick(const Block_Location& location, Chunk& chunk)
    {
        std::cout << "bye bye" << std::endl;
        Block_Location lightLoc (location.x, location.y + 1, location.z);

        if (chunk.getBlockLight(lightLoc) < 3 || chunk.getNaturalLight(lightLoc) < 3)
        {
            chunk.addBlock(location, Block::get(Block::ID::Dirt));
        }
    }



    Interaction_Type Grass::interact(Chunk& chunk, const Block_Location& location, Temp_Item_ID id) const
    {
        //if id == hoe ...
            //chunk -> this location = "empty farm tile"
            //return -> change

        //if id == shovel ...
            //chunk -> this location = "path tile"
            //return -> change

        //else
        {
            return Interaction_Type::None;
        }
    }

}

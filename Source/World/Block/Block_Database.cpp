#include "Block_Database.h"

#include <iostream>


#include "Block_Types/BDefault.h"

#include "../../Util/File_Util.h"

namespace Block
{
    Database& Database::get()
    {
        static Database database;
        return database;
    }

    Database::Database()
    :   blocks ((int)ID::NUM_BLOCK_TYPES)
    ,   textures   ("Texture_Atlas", 512, 16)
    {
/*
        auto blockNames = getFileNamesFromFolder("Data/Blocks");
        for (auto& name : blockNames)
        {
            std::cout << name << std::endl;
        }
*/

        blocks[(int)ID::Air     ] = std::make_unique<Default>   ("Air");
        blocks[(int)ID::Grass   ] = std::make_unique<Default>   ("Grass");
        blocks[(int)ID::Dirt    ] = std::make_unique<Default>   ("Dirt");
        blocks[(int)ID::Stone   ] = std::make_unique<Default>   ("Stone");
        blocks[(int)ID::Sand    ] = std::make_unique<BSand>     ();

        blocks[(int)ID::Oak_Wood    ] = std::make_unique<Default>       ("Oak_Wood");
        blocks[(int)ID::Oak_Leaf    ] = std::make_unique<Default>       ("Oak_Leaf");

        blocks[(int)ID::Water       ] = std::make_unique<Default>       ("Water");

        blocks[(int)ID::Snow       ] = std::make_unique<Default>        ("Snow");

        blocks[(int)ID::Rose       ] = std::make_unique<Default>        ("Rose");
        blocks[(int)ID::Tall_Grass       ] = std::make_unique<Default>  ("Tall_Grass");
    }

    const Type& Database::getBlock(uint8_t id)
    {
        return *blocks[id];
    }

    const Type& Database::getBlock(ID blockID)
    {
        return *blocks[(int)blockID];
    }


    const Type& get(uint8_t id)
    {
        return Database::get().getBlock(id);
    }

    const Type& get(ID blockID)
    {
        return Database::get().getBlock(blockID);
    }

}

#include "Block_Database.h"


#include "Block_Types/BDefault.h"

namespace Block
{
    Database& Database::get()
    {
        static Database database;
        return database;
    }

    Database::Database()
    :   blocks ((int)ID::NUM_BLOCK_TYPES)
    ,   textures   ("Texture_Atlas_Plastic", 512, 16)
    {
        blocks[(int)ID::Air     ] = std::make_unique<Default>  ("Air");
        blocks[(int)ID::Grass   ] = std::make_unique<Default>  ("Grass");
        blocks[(int)ID::Dirt    ] = std::make_unique<Default>  ("Dirt");
        blocks[(int)ID::Stone   ] = std::make_unique<Default>  ("Stone");
        blocks[(int)ID::Sand    ] = std::make_unique<Default>  ("Sand");
    }

    const Type& Database::getBlock(uint8_t id)
    {
        return *blocks[id];
    }

    const Type& Database::getBlock(ID blockID)
    {
        return *blocks[(int)blockID];
    }
}

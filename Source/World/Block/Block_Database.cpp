#include "Block_Database.h"

#include <iostream>


#include "Block_Types/BDefault.h"
#include "Block_Types/BPlant.h"
#include "Block_Types/BWater.h"

#include "../../Util/File_Util.h"

namespace Block
{
    Database& Database::get()
    {
        static Database database;
        return database;
    }

    Database::Database()
    :   m_textures  ("Atlas/Low", 512, 16)
    {
        m_blocks[(int)ID::Air     ] = std::make_unique<Default>   ("Air");
        m_blocks[(int)ID::Grass   ] = std::make_unique<Default>   ("Grass");
        m_blocks[(int)ID::Dirt    ] = std::make_unique<Default>   ("Dirt");
        m_blocks[(int)ID::Stone   ] = std::make_unique<Default>   ("Stone");
        m_blocks[(int)ID::Sand    ] = std::make_unique<BSand>     ();

        m_blocks[(int)ID::Oak_Wood    ] = std::make_unique<Default> ("Oak_Wood");
        m_blocks[(int)ID::Oak_Leaf    ] = std::make_unique<Default> ("Oak_Leaf");

        m_blocks[(int)ID::Water       ] = std::make_unique<BWater> ();

        m_blocks[(int)ID::Rose        ] = std::make_unique<BPlant> ("Rose");
        m_blocks[(int)ID::Tall_Grass  ] = std::make_unique<BPlant> ("Tall_Grass");
    }

    const Type& Database::getBlock(uint8_t id) const
    {
        return *m_blocks[id];
    }

    const Type& Database::getBlock(ID blockID) const
    {
        return *m_blocks[(int)blockID];
    }

    const Texture::Atlas& Database::getTextureAtlas() const
    {
        return m_textures;
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

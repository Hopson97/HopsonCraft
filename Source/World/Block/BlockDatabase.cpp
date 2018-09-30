#include "BlockDatabase.h"

#include <iostream>


#include "Types/DefaultBlock.h"
#include "Types/PlantBlock.h"

#include "../../Util/FileUtil.h"

BlockDatabase& BlockDatabase::get()
{
    static BlockDatabase database;
    return database;
}

BlockDatabase::BlockDatabase()
:   m_textures  ("Atlas/Low", 512, 16)
{
    m_blocks[(int)BlockID::Air     ] = std::make_unique<DefaultBlock> ("Air");
    m_blocks[(int)BlockID::Grass   ] = std::make_unique<DefaultBlock> ("Grass");
    m_blocks[(int)BlockID::Dirt    ] = std::make_unique<DefaultBlock> ("Dirt");
    m_blocks[(int)BlockID::Stone   ] = std::make_unique<DefaultBlock> ("Stone");
    m_blocks[(int)BlockID::Sand    ] = std::make_unique<DefaultBlock> ("Sand");

    m_blocks[(int)BlockID::Oak_Wood    ] = std::make_unique<DefaultBlock> ("Oak_Wood");
    m_blocks[(int)BlockID::Oak_Leaf    ] = std::make_unique<DefaultBlock> ("Oak_Leaf");

    m_blocks[(int)BlockID::Water       ] = std::make_unique<DefaultBlock> ("Water");

    m_blocks[(int)BlockID::Rose        ] = std::make_unique<PlantBlock> ("Rose");
    m_blocks[(int)BlockID::Tall_Grass  ] = std::make_unique<PlantBlock> ("Tall_Grass");
}

const BlockType& BlockDatabase::getBlock(uint8_t id) const
{
    return *m_blocks[id];
}

const BlockType& BlockDatabase::getBlock(BlockID blockID) const
{
    return *m_blocks[(int)blockID];
}

const TextureAtlas& BlockDatabase::getTextureAtlas() const
{
    return m_textures;
}

const BlockType& get(uint8_t id)
{
    return BlockDatabase::get().getBlock(id);
}

const BlockType& get(BlockID blockID)
{
    return BlockDatabase::get().getBlock(blockID);
}



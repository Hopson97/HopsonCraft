#ifndef BlockDatabase_H_INCLUDED
#define BlockDatabase_H_INCLUDED

#include <memory>
#include <array>

#include "Types/BlockType.h"
#include "BlockID.h"

#include "../../Texture/Texture_Atlas.h"

namespace Block
{
    class Database
    {
        public:
            static Database& get();

            Database(const Database& other)             = delete;
            Database& operator =(const Database& other) = delete;

            Database(Database&& other)             = delete;
            Database& operator =(Database&& other) = delete;

            const BlockType& getBlock(uint8_t id) const;
            const BlockType& getBlock(ID blockID) const;

            const Texture::Atlas& getTextureAtlas() const;

        private:
            Database();

            std::array<std::unique_ptr<BlockType>, (int)ID::NUM_BlockTypeS> m_blocks;

            Texture::Atlas m_textures;
    };

    const BlockType& get(uint8_t id);
    const BlockType& get(ID blockID);
}

#endif // BlockDatabase_H_INCLUDED

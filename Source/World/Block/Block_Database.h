#ifndef BLOCK_DATABASE_H_INCLUDED
#define BLOCK_DATABASE_H_INCLUDED

#include <memory>
#include <array>

#include "Block_Types/Block_Type.h"
#include "Block_ID.h"

#include "../../Texture/Texture_Atlas.h"

namespace Block
{
    class Database
    {
        public:
            static Database& get();

            Database();

            const Type& getBlock(uint8_t id) const;
            const Type& getBlock(ID blockID) const;

            const Texture::Atlas& getTextureAtlas() const;

        private:
            std::array<std::unique_ptr<Type>, (int)ID::NUM_BLOCK_TYPES> m_blocks;

            Texture::Atlas m_textures;
    };

    const Type& get(uint8_t id);
    const Type& get(ID blockID);
}

#endif // BLOCK_DATABASE_H_INCLUDED

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

            Database();

            const Type& getBlock(uint8_t id) const;
            const Type& getBlock(ID blockID) const;

            const Texture::Atlas& getTextureAtlas() const;

        private:
            std::array<std::unique_ptr<Type>, (int)ID::NUM_BlockTypeS> m_blocks;

            Texture::Atlas m_textures;
    };

    const Type& get(uint8_t id);
    const Type& get(ID blockID);
}

#endif // BlockDatabase_H_INCLUDED

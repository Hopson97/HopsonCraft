#ifndef BlockDatabase_H_INCLUDED
#define BlockDatabase_H_INCLUDED

#include <memory>
#include <array>

#include "Types/BlockType.h"
#include "BlockID.h"

#include "../../Texture/TextureAtlas.h"
#include "../../Util/Singleton.h"

namespace Block
{
    class Database : public Singleton
    {
        public:
            static Database& get();

            const BlockType& getBlock(uint8_t id) const;
            const BlockType& getBlock(ID blockID) const;

            const TextureAtlas& getTextureAtlas() const;

        private:
            Database();

            std::array<std::unique_ptr<BlockType>, (int)ID::NUM_BlockTypeS> m_blocks;

            TextureAtlas m_textures;
    };

    const BlockType& get(uint8_t id);
    const BlockType& get(ID blockID);
}

#endif // BlockDatabase_H_INCLUDED

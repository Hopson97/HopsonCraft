#ifndef BlockDatabase_H_INCLUDED
#define BlockDatabase_H_INCLUDED

#include <memory>
#include <array>

#include "Types/BlockType.h"
#include "BlockID.h"

#include "../../Texture/TextureAtlas.h"
#include "../../Util/Singleton.h"

class BlockDatabase : public Singleton
{
    public:
        static BlockDatabase& get();

        const BlockType& getBlock(uint8_t id) const;
        const BlockType& getBlock(BlockID blockID) const;

        const TextureAtlas& getTextureAtlas() const;

    private:
        BlockDatabase();

        std::array<std::unique_ptr<BlockType>, (int)BlockID::NUM_BlockTypeS> m_blocks;

        TextureAtlas m_textures;
};

const BlockType& get(uint8_t id);
const BlockType& get(BlockID blockID);


#endif // BlockDatabase_H_INCLUDED

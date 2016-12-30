#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include <array>
#include <cstdint>
#include <vector>

#include "../World_Constants.h"
#include "../Block/Block_Type/Block_Type.h"
#include "../Block/D_Blocks.h"

class Chunk_Layer
{
    public:
        Chunk_Layer();

        void setBlock(int x, int z, const Block::Block_Type& block);

        const Block::Block_Type& getBlock (int x, int z) const;

        bool hasTranslucentBlocks() const;

        uint8_t getNaturalLight    (int x, int z) const;
        uint8_t getBlockLight      (int x, int z) const;

    private:
        std::array<uint8_t, World_Constants::CHUNK_AREA>    m_blocks;

        std::array<uint8_t, World_Constants::CHUNK_AREA>    m_naturalLightMap;
        std::array<uint8_t, World_Constants::CHUNK_AREA>    m_blockLightMap;

        uint16_t m_translucentCount = World_Constants::CHUNK_AREA;
};

#endif // CHUNK_LAYER_H

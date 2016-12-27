#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include <array>
#include <cstdint>

#include "../Block/Block_Type/Block_Type.h"
#include "../Block/D_Blocks.h"

class Chunk_Layer
{
    public:
        Chunk_Layer();

        void setBlock(int x, int z, const Block::Block_Type& block);

        const Block::Block_Type& getBlock (int x, int z) const;

        bool hasAirBlocks() const;

    private:
        std::array<uint8_t, 20 * 20> m_blocks;

        uint16_t m_airBlockCount = 20 * 20;
};

#endif // CHUNK_LAYER_H

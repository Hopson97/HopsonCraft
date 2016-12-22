#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include <vector>

#include "../Block/Block.h"
#include "../Block/D_Blocks.h"

class Chunk_Layer
{
    struct Block_Pointer
    {
        Block_Pointer() = default;
        Block_Pointer(Block::ID id)
        :   id ((uint8_t) id)
        {}

        uint8_t id = (uint8_t) Block::ID::Air;
    };


    public:
        Chunk_Layer();

        void setBlock(int x, int z, const Block_t& block);

        const Block_t& getBlock (int x, int z) const;

    private:
        std::vector<Block_Pointer> m_blocks;
};

#endif // CHUNK_LAYER_H

#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include <array>

#include "../Block/Block_Type/Block_Type.h"
#include "../Block/D_Blocks.h"
#include "../World_Constants.h"

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

        void setBlock(int x, int z, const Block::Block_Type& block);

        const Block::Block_Type& getBlock (int x, int z) const;

    private:
        std::array<Block_Pointer, World::CHUNK_SIZE * World::CHUNK_SIZE> m_blocks;
};

#endif // CHUNK_LAYER_H

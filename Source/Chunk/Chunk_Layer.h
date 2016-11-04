#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include <vector>

#include "Block/Block.h"

class Chunk_Layer
{
    public:
        Chunk_Layer();

        void setBlock(int x, int z, Block::Block_Base& block);

        const Block::Block_Base& getBlock (int x, int z) const;

    private:
        std::vector<Block::Block_Base*> m_blocks;
};

#endif // CHUNK_LAYER_H

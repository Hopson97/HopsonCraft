#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include "Block.h"
#include "Air.h"

#include <vector>

class Chunk_Layer
{
    public:
        Chunk_Layer();

        const Block::Block_Base& getBlock (const Vector2& location) const;

        void setBlock (Block::Block_Base& block, const Vector2& location);

        bool isEmpty () const; //Returns true if all the blocks are just air blocks

    private:
        std::vector<Block::Block_Base*> m_blocks;
        bool m_isEmpty = true;
        uint8_t m_blockCount = 0;
};

#endif // CHUNK_LAYER_H

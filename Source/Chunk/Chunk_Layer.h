#ifndef CHUNK_LAYER_H
#define CHUNK_LAYER_H

#include <vector>

#include "Block/Block.h"

class Chunk_Layer
{
    public:
        Chunk_Layer();

        void setBlock(int x, int z, const Block_t& block);

        const Block_t& getBlock (int x, int z) const;

    private:
        std::vector<const Block_t*> m_blocks;
};

#endif // CHUNK_LAYER_H

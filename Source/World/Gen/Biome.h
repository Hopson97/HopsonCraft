#ifndef BIOME_H
#define BIOME_H

#include <vector>

#include "../Block/Block.h"

class Biome
{
    struct Surface_Block
    {
        Surface_Block (const Block_t& block, int freq)
        :   block       (&block)
        ,   frequency   (freq) { }

        const Block_t*  block;
        const int       frequency;
    };

    public:
        void setDepth(int depth);
        void addBlock(const Block_t& block, int frequency);

        const Block_t& getBlock() const;

        int getDepth() const;

    private:
        std::vector<Surface_Block> m_blocks;
        int m_totalFrequency;
        int m_depth;
};

#endif // BIOME_H

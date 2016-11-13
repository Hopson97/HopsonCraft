#ifndef BIOME_H
#define BIOME_H

#include <vector>

#include "../Block/Block.h"
#include "Structure.h"

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
        void addTree (Structure_Function function);
        Structure_Function getTreeFunction();

        const Block_t& getBlock() const;

        int getDepth() const;

    private:
        std::vector<Surface_Block>      m_blocks;
        std::vector<Structure_Function> m_treeCreators;

        int m_totalFrequency;
        int m_depth;
};

#endif // BIOME_H

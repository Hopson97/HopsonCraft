#ifndef BIOME_H
#define BIOME_H

#include <vector>

#include "../Block/Block.h"
#include "Structure.h"
#include "../Block/Block.h"
#include "../../Util/Random.h"

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
        void setTreeFrequency(int frequency);

        void addBlock(const Block_t& block, int frequency);
        void addTree (Structure_Function function);
        void addFlora(const Block_t& block);

        Structure_Function getTreeFunction();
        const Block_t& getBlock() const;
        const Block_t& getFlora() const;
        int getDepth() const;
        int getTreeFrequency() const;

    private:
        std::vector<Surface_Block>         m_blocks;
        std::vector<Structure_Function>     m_treeCreators;
        std::vector<const Block_t*>         m_flora;

        int m_totalFrequency;
        int m_depth;
        int m_treeFrequency;
};

#endif // BIOME_H

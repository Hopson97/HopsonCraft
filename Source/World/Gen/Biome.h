#ifndef BIOME_H
#define BIOME_H

#include <vector>

#include "Structure.h"
#include "../Block/Block_Type/Block_Type.h"
#include "../../Util/Random.h"

class Biome
{
    public:
        void setDepth(int depth);
        void setTreeFrequency(int frequency);
        void setFloraFrequency(int frequency);

        void addBlock(const Block::Block_Type& block, int frequency);
        void addFlora(const Block::Block_Type& block, int frequency);
        void addTree (Structure_Function function);

        bool hasFlora();
        bool hasTrees();

        Structure_Function getTreeFunction();
        const Block::Block_Type& getBlock() const;
        const Block::Block_Type& getFlora() const;
        int getDepth() const;

        int getTreeFrequency() const;
        int getFloraFrequency() const;

    private:
        std::vector<const Block::Block_Type*>   m_blocks;
        std::vector<const Block::Block_Type*>   m_flora;
        std::vector<Structure_Function>         m_treeCreators;


        int m_depth          = 1;
        int m_treeFrequency  = 1;
        int m_floraFrequency = 1;
};

#endif // BIOME_H

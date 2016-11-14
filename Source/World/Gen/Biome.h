#ifndef BIOME_H
#define BIOME_H

#include <vector>

#include "../Block/Block.h"
#include "Structure.h"
#include "../Block/Block.h"
#include "../../Util/Random.h"

class Biome
{
    public:
        void setDepth(int depth);
        void setTreeFrequency(int frequency);
        void setFloraFrequency(int frequency);

        void addBlock(const Block_t& block, int frequency);
        void addFlora(const Block_t& block, int frequency);
        void addTree (Structure_Function function);


        Structure_Function getTreeFunction();
        const Block_t& getBlock() const;
        const Block_t& getFlora() const;
        int getDepth() const;

        int getTreeFrequency() const;
        int getFloraFrequency() const;

    private:
        std::vector<const Block_t*>         m_blocks;
        std::vector<const Block_t*>         m_flora;
        std::vector<Structure_Function>     m_treeCreators;


        int m_depth          = 1;
        int m_treeFrequency  = 1;
        int m_floraFrequency = 1;
};

#endif // BIOME_H

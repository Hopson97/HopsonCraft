#ifndef BPLANT_H_INCLUDED
#define BPLANT_H_INCLUDED

#include "BlockType.h"


class PlantBlock : public BlockType
{
    public:
        PlantBlock(std::string&& name);
        void trigger(World& world, CBlock& block, const BlockPosition& position) const override;
};

#endif // BPLANT_H_INCLUDED

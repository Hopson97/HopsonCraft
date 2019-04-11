#ifndef IBLOCK_ACCESSIBLE_H_INCLUDED
#define IBLOCK_ACCESSIBLE_H_INCLUDED

#include "Chunk/Nodes.h"

struct IBlock_Accessible
{
    virtual void setBlock   (int x, int y, int z, CBlock block) = 0;
    virtual CBlock getBlock (int x, int y, int z) const = 0;


    virtual CBlock qGetBlock(int x, int y, int z) const
    {
        return getBlock(x, y, z);
    }

    virtual void qSetBlock  (int x, int y, int z, CBlock block)
    {
        setBlock(x, y, z, block);
    }
};

#endif // IBLOCK_ACCESSIBLE_H_INCLUDED

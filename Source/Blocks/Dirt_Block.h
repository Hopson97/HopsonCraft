#ifndef DIRT_BLOCK_H
#define DIRT_BLOCK_H

#include "Block.h"


class Dirt_Block : public Block
{
    public:
        Dirt_Block();

        std::vector<GLfloat> getSideTxrCoords   () const override;
        std::vector<GLfloat> getTopTxrCoords    () const override;
        std::vector<GLfloat> getBottomTxrCoords () const override;

    private:
};

#endif // DIRT_BLOCK_H

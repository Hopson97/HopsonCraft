#ifndef STONE_BLOCK_H
#define STONE_BLOCK_H

#include "Block.h"

class Stone_Block : public Block
{
    public:
        Stone_Block();

        std::vector<GLfloat> getSideTxrCoords   () const override;
        std::vector<GLfloat> getTopTxrCoords    () const override;
        std::vector<GLfloat> getBottomTxrCoords () const override;
};

#endif // STONE_BLOCK_H

#ifndef GRASS_BLOCK_H
#define GRASS_BLOCK_H

#include "Block.h"

class Grass_Block : public Block
{
    public:
        Grass_Block();

        std::vector<GLfloat> getSideTxrCoords   () const override;
        std::vector<GLfloat> getTopTxrCoords    () const override;
        std::vector<GLfloat> getBottomTxrCoords () const override;

};

#endif // GRASS_BLOCK_H

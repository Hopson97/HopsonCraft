#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

namespace Block
{
    struct Dirt : public Block_Base
    {
        bool isOpaque   () const override;
        Id   getID      () const override;

        Vector2 getTextureTop   () const override;
        Vector2 getTextureSide  () const override;
        Vector2 getTextureBottom() const override;
    };
}

#endif // DIRT_H

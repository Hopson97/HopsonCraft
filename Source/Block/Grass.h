#ifndef GRASS_H
#define GRASS_H

#include "Block.h"

namespace Block
{
    struct Grass : public Block_Base
    {
        bool isOpaque   () const override;
        Id   getID      () const override;

        Vector2 getTextureTop   () const override;
        Vector2 getTextureSide  () const override;
        Vector2 getTextureBottom() const override;

    };
}

#endif // GRASS_H

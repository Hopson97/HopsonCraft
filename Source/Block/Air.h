#ifndef AIR_H
#define AIR_H

#include "Block.h"

namespace Block
{
    struct Air : public Block_Base
    {
        bool isOpaque   () const override;
        Id   getID      () const override;

        Vector2 getTextureTop   () const override;
        Vector2 getTextureSide  () const override;
        Vector2 getTextureBottom() const override;

    };
}

#endif // AIR_H

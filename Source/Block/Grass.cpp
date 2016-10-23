#include "Grass.h"

#include <iostream>

namespace Block
{
    bool Grass::isOpaque () const
    {
        return true;
    }

    Id Grass::getID () const
    {
        return Id::Grass;
    }

    Vector2 Grass::getTextureTop () const
    {
        return {0, 0};
    }

    Vector2 Grass::getTextureSide () const
    {
        return {1, 0};
    }

    Vector2 Grass::getTextureBottom () const
    {
        return {2, 0};
    }
}

#include "Stone.h"

namespace Block
{
    bool Stone::isOpaque () const
    {
        return true;
    }

    Id Stone::getID () const
    {
        return Id::Stone;
    }

    Vector2 Stone::getTextureTop () const
    {
        return {3, 0};
    }

    Vector2 Stone::getTextureSide () const
    {
        return {3, 0};
    }

    Vector2 Stone::getTextureBottom () const
    {
        return {3, 0};
    }
}

#include "Stone.h"

namespace Block
{
    Stone :: Stone()
    { }

    Vector2 Stone :: getTextureTop () const
    {
        return { 3, 0 };
    }

    Vector2 Stone :: getTextureSide () const
    {
        return { 3, 0 };
    }

    Vector2 Stone :: getTextureBottom () const
    {
        return { 3, 0 };
    }

    bool Stone :: isOpaque () const
    {
        return true;
    }

    ID Stone :: getID () const
    {
        return ID::Stone;
    }
} //Namespace Block

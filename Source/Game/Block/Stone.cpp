#include "Stone.h"

namespace Block
{
    Stone :: Stone()
    :   Block_Base ( ID::Stone )
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
} //Namespace Block

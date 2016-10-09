#include "dirt.h"

namespace Block
{
    Dirt :: Dirt()
    :   Block_Base ( ID::Dirt )
    {  }

    Vector2 Dirt :: getTextureTop () const
    {
        return { 2, 0 };
    }

    Vector2 Dirt :: getTextureSide () const
    {
        return { 2, 0 };
    }

    Vector2 Dirt :: getTextureBottom () const
    {
        return { 2, 0 };
    }

    bool Dirt :: isOpaque () const
    {
        return true;
    }
} //Namespace Block

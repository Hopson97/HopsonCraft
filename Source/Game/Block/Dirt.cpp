#include "dirt.h"

namespace Block
{
    Dirt :: Dirt()
    :   Block_Base ( true )
    {
        //ctor
    }

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
} //Namespace Block

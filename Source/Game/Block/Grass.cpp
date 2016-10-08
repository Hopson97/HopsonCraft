#include "grass.h"

namespace Block
{
    Grass :: Grass()
    :   Block_Base ( ID::Grass )
    {  }

    Vector2 Grass :: getTextureTop () const
    {
        return { 0, 0 };
    }

    Vector2 Grass :: getTextureSide () const
    {
        return { 1, 0 };
    }

    Vector2 Grass :: getTextureBottom () const
    {
        return { 2, 0 };
    }
} //Namespace Block


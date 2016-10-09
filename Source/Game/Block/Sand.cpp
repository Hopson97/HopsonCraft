#include "Sand.h"

namespace Block
{
    Sand :: Sand()
    :   Block_Base ( ID::Sand )
    {  }

    Vector2 Sand :: getTextureTop () const
    {
        return { 4, 0 };
    }

    Vector2 Sand :: getTextureSide () const
    {
        return { 4, 0 };
    }

    Vector2 Sand :: getTextureBottom () const
    {
        return { 4, 0 };
    }

    bool Sand :: isOpaque () const
    {
        return true;
    }
} //Namespace Block

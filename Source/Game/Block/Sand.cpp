#include "Sand.h"

namespace Block
{
    Sand :: Sand()
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

    ID Sand :: getID () const
    {
        return ID::Sand;
    }
} //Namespace Block

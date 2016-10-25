#include "Oak_Wood.h"

namespace Block
{
    Oak_Wood :: Oak_Wood()
    {  }

    Vector2 Oak_Wood :: getTextureTop () const
    {
        return { 6, 0 };
    }

    Vector2 Oak_Wood :: getTextureSide () const
    {
        return { 6, 0 };
    }

    Vector2 Oak_Wood :: getTextureBottom () const
    {
        return { 6, 0 };
    }

    bool Oak_Wood :: isOpaque () const
    {
        return true;
    }

    ID Oak_Wood :: getID () const
    {
        return ID::Oak_Wood;
    }
} //Namespace Block

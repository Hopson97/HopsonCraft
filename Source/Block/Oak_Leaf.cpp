#include "Oak_Leaf.h"

namespace Block
{
    Oak_Leaf :: Oak_Leaf()
    {  }

    Vector2 Oak_Leaf :: getTextureTop () const
    {
        return { 7, 0 };
    }

    Vector2 Oak_Leaf :: getTextureSide () const
    {
        return { 7, 0 };
    }

    Vector2 Oak_Leaf :: getTextureBottom () const
    {
        return { 7, 0 };
    }

    ID Oak_Leaf :: getID () const
    {
        return ID::Oak_Leaf;
    }
} //Namespace Block

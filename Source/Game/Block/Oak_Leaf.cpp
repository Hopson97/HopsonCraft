#include "Oak_Leaf.h"

namespace Block
{
    Oak_Leaf :: Oak_Leaf()
    :   Block_Base ( ID::Oak_Leaf )
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
} //Namespace Block

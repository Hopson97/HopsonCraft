#include "Water.h"

namespace Block
{
    Water :: Water()
    {  }

    Vector2 Water :: getTextureTop () const
    {
        return { 5, 0 };
    }

    Vector2 Water :: getTextureSide () const
    {
        return { 5, 0 };
    }

    Vector2 Water :: getTextureBottom () const
    {
        return { 5, 0 };
        return { 5, 0 };
    }

    ID Water :: getID () const
    {
        return ID::Water;
    }
} //Namespace Block

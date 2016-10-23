#include "air.h"

namespace Block
{
    bool Air::isOpaque () const
    {
        return false;
    }

    Id Air::getID () const
    {
        return Id::Air;
    }

    Vector2 Air::getTextureTop () const
    {
        return {0, 0};
    }

    Vector2 Air::getTextureSide () const
    {
        return {0, 0};
    }

    Vector2 Air::getTextureBottom () const
    {
        return {0, 0};
    }
}

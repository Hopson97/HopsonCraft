#include "Dirt.h"

namespace Block
{
    bool Dirt::isOpaque () const
    {
        return true;
    }

    Id Dirt::getID () const
    {
        return Id::Dirt;
    }

    Vector2 Dirt::getTextureTop () const
    {
        return {2, 0};
    }

    Vector2 Dirt::getTextureSide () const
    {
        return {2, 0};
    }

    Vector2 Dirt::getTextureBottom () const
    {
        return {2, 0};
    }
}

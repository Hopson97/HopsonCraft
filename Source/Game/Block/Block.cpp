#include "block.h"

#include <iostream>

namespace Block
{
    Block_Base :: Block_Base( bool isOpaque, ID id )
    :   m_isOpaque  ( isOpaque )
    ,   m_id        ( id       )
    {
    }

    Vector2 Block_Base :: getTextureTop () const
    {
        return { 0, 0 };
    }

    Vector2 Block_Base :: getTextureSide () const
    {
        return { 0, 0 };
    }

    Vector2 Block_Base :: getTextureBottom () const
    {
        return { 0, 0 };
    }

    bool Block_Base :: isOpaque () const
    {
        return m_isOpaque;
    }

    ID Block_Base :: getID () const
    {
        return m_id;
    }

} //Namespace Block

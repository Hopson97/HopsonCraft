#include "Stone_Block.h"

Stone_Block :: Stone_Block()
:   Block ( Block_Type::Stone )
{
    //ctor
}

//Texture/ OpenGL stuff:

std::vector<GLfloat> Stone_Block :: getSideTxrCoords () const
{
    static const std::vector<GLfloat> sideTextures =
    {
        1,    0,
        1,    1,
        0.75,   1,

        0.75,   0,
        1,    0,
        0.75,   1
    };

    return sideTextures;
}
std::vector<GLfloat> Stone_Block::getTopTxrCoords() const
{
    static const std::vector<GLfloat> sideTextures =
    {
        1,    0,
        1,    1,
        0.75,   1,

        0.75,   0,
        1,    0,
        0.75,   1
    };

    return sideTextures;
}

std::vector<GLfloat> Stone_Block :: getBottomTxrCoords() const
{
    static const std::vector<GLfloat> sideTextures =
    {
        1,    0,
        1,    1,
        0.75,   1,

        0.75,   0,
        1,    0,
        0.75,   1
    };

    return sideTextures;
}

#include "Grass_Block.h"

Grass_Block :: Grass_Block()
:   Block ( Block_Type::Grass )
{
    //ctor
}










//Texture/ OpenGL stuff:

std::vector<GLfloat> Grass_Block :: getSideTxrCoords () const
{
    static const std::vector<GLfloat> sideTextures =
    {
        0.5,    0,
        0.5,    1,
        0.25,   1,

        0.25,   0,
        0.5,    0,
        0.25,   1
    };

    return sideTextures;
}
std::vector<GLfloat> Grass_Block::getTopTxrCoords() const
{
    static const std::vector<GLfloat> topTextures =
    {
        0.25,   0,
        0.25,   1,
        0.0,    1,

        0.0,    0,
        0.25,   0,
        0.0,    1
    };

    return topTextures;
}

std::vector<GLfloat> Grass_Block :: getBottomTxrCoords() const
{
    static const std::vector<GLfloat> bottomTextures =
    {
        0.75,   0,
        0.75,   1,
        0.5,    1,

        0.5,    0,
        0.75,   0,
        0.5,    1
    };

    return bottomTextures;
}

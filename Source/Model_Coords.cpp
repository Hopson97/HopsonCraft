#include "Model_Coords.h"


std::vector<GLfloat> getCubeVerticies(float size)
{
    return
    {
        //Back
        1 + size,   -size,      -size,
        -size,      -size,      -size,
        -size,      1 + size,   -size,
        1 + size,   1 + size,   -size,

        //Right-Side
        1 + size, -size,    1 + size,
        1 + size, -size,    -size,
        1 + size, 1 + size, -size,
        1 + size, 1 + size, 1 + size,

        //Front
        -size,      -size,      1 + size,
        1 + size,   -size,      1 + size,
        1 + size,   1 + size,   1 + size,
        -size,      1 + size,   1 + size,

        //Left
        -size, -size,       -size,
        -size, -size,       1 + size,
        -size, 1 + size,    1 + size,
        -size, 1 + size,    -size,

        //Top
        -size,      1 + size, 1 + size,
        1 + size,   1 + size, 1 + size,
        1 + size,   1 + size, -size,
        -size,      1 + size, -size,

        //Bottom
        -size,      -size, -size,
        1 + size,   -size, -size,
        1 + size,   -size, 1 + size,
        -size,      -size, 1
    };
}

std::vector<GLuint> getCubeIndices()
{
    return
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
}



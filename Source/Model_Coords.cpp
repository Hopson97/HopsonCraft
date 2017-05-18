#include "Model_Coords.h"


std::vector<GLfloat> getCubeVerticies(float enlarger)
{
    return
    {
        //Back
        1 + enlarger,   -enlarger,      -enlarger,
        -enlarger,      -enlarger,      -enlarger,
        -enlarger,      1 + enlarger,   -enlarger,
        1 + enlarger,   1 + enlarger,   -enlarger,

        //Right-Side
        1 + enlarger, -enlarger,        1 + enlarger,
        1 + enlarger, -enlarger,        -enlarger,
        1 + enlarger, 1 + enlarger,     -enlarger,
        1 + enlarger, 1 + enlarger,     1 + enlarger,

        //Front
        -enlarger,      -enlarger,      1 + enlarger,
        1 + enlarger,   -enlarger,      1 + enlarger,
        1 + enlarger,   1 + enlarger,   1 + enlarger,
        -enlarger,      1 + enlarger,   1 + enlarger,

        //Left
        -enlarger, -enlarger,           -enlarger,
        -enlarger, -enlarger,           1 + enlarger,
        -enlarger, 1 + enlarger,        1 + enlarger,
        -enlarger, 1 + enlarger,        -enlarger,

        //Top
        -enlarger,      1 + enlarger,   1 + enlarger,
        1 + enlarger,   1 + enlarger,   1 + enlarger,
        1 + enlarger,   1 + enlarger,   -enlarger,
        -enlarger,      1 + enlarger,   -enlarger,

        //Bottom
        -enlarger,      -enlarger,      -enlarger,
        1 + enlarger,   -enlarger,      -enlarger,
        1 + enlarger,   -enlarger,      1 + enlarger,
        -enlarger,      -enlarger,      1
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



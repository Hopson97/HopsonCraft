#include "Model_Coords.h"


std::vector<GLfloat> getCubeVerticies(float scale)
{
    return
    {
        //Back
        1 * scale,  0,          0,
        0,          0,          0,
        0,          1 * scale,  0,
        1 * scale,  1 * scale,  0,

        //Right-Side
        1 * scale, 0,           1 * scale,
        1 * scale, 0,           0,
        1 * scale, 1 * scale,   0,
        1 * scale, 1 * scale,   1 * scale,

        //Front
        0,          0,          1 * scale,
        1 * scale,  0,          1 * scale,
        1 * scale,  1 * scale,  1 * scale,
        0,          1 * scale,  1 * scale,

        //Left
        0, 0,           0,
        0, 0,           1 * scale,
        0, 1 * scale,   1 * scale,
        0, 1 * scale,   0,

        //Top
        0,          1 * scale,   1 * scale,
        1 * scale,  1 * scale,   1 * scale,
        1 * scale,  1 * scale,   0,
        0,          1 * scale,   0,

        //Bottom
        0,          0,  0,
        1 * scale,  0,  0,
        1 * scale,  0,  1 * scale,
        0,          0,  1 * scale
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



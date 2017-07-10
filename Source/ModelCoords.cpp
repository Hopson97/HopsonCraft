#include "ModelCoords.h"

std::vector<GLfloat> getCubeVerticies(float posScale, float negScale)
{
    return
    {
        //Back
         1 * posScale,  -1 * negScale,  -1 * negScale,
        -1 * negScale,  -1 * negScale,  -1 * negScale,
        -1 * negScale,   1 * posScale,  -1 * negScale,
         1 * posScale,   1 * posScale,  -1 * negScale,

        //Right-Side
        1 * posScale, -1 * negScale,     1 * posScale,
        1 * posScale, -1 * negScale,    -1 * negScale,
        1 * posScale,  1 * posScale,    -1 * negScale,
        1 * posScale,  1 * posScale,     1 * posScale,

        //Front
        -1 * negScale,  -1 * negScale,  1 * posScale,
         1 * posScale,  -1 * negScale,  1 * posScale,
         1 * posScale,   1 * posScale,  1 * posScale,
        -1 * negScale,   1 * posScale,  1 * posScale,

        //Left
        -1 * negScale, -1 * negScale,   -1 * negScale,
        -1 * negScale, -1 * negScale,    1 * posScale,
        -1 * negScale,  1 * posScale,    1 * posScale,
        -1 * negScale,  1 * posScale,   -1 * negScale,

        //Top
        -1 * negScale,  1 * posScale,    1 * posScale,
         1 * posScale,  1 * posScale,    1 * posScale,
         1 * posScale,  1 * posScale,   -1 * negScale,
        -1 * negScale,  1 * posScale,   -1 * negScale,

        //Bottom
        -1 * negScale,  -1 * negScale,  -1 * negScale,
         1 * posScale,  -1 * negScale,  -1 * negScale,
         1 * posScale,  -1 * negScale,   1 * posScale,
        -1 * negScale,  -1 * negScale,   1 * posScale
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



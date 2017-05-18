#ifndef MODEL_COORDS_H_INCLUDED
#define MODEL_COORDS_H_INCLUDED

#include <vector>
#include <GL/glew.h>

struct Model_Data
{
    std::vector<GLfloat>    vertexCoords;
    std::vector<GLfloat>    textureCoords;
    std::vector<GLuint>     indices;
};

std::vector<GLfloat>    getCubeVerticies   (float enlarger = 0.0f);
std::vector<GLuint>     getCubeIndices     ();

#endif // MODEL_COORDS_H_INCLUDED

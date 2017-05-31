#ifndef MODEL_COORDS_H_INCLUDED
#define MODEL_COORDS_H_INCLUDED

#include <vector>
#include <GL/glew.h>

struct ModelData
{
    std::vector<GLfloat>    vertexCoords;
    std::vector<GLfloat>    textureCoords;
    std::vector<GLuint>     indices;
};

std::vector<GLfloat>    getCubeVerticies   (float scale = 1.0f);
std::vector<GLuint>     getCubeIndices     ();

#endif // MODEL_COORDS_H_INCLUDED

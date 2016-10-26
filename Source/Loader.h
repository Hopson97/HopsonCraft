#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <memory>

#include "../OpenGL/Glew/glew.h"

#include "Model.h"

namespace Loader
{
    Model_Data loadArrayMesh (  const std::vector<GLfloat>& vertexCoords,
                                const std::vector<GLfloat>& textureCoords );
/*
    Model_Data loadElementMesh ( const std::vector<GLfloat>& vertexCoords,
                                 const std::vector<GLfloat>& textureCoords,
                                 const std::vector<GLuint>&  indices );
*/
    GLuint      loadTexture ( const std::string& file );
}

#endif // LOADER_H

#ifndef SHADER_LOADER_H_INCLUDED
#define SHADER_LOADER_H_INCLUDED

#include "../OpenGL/Glew/glew.h"
#include <string>

GLuint loadShader( 	const std::string& vertexFilePath,
					const std::string& fragmentFilePath );



#endif // SHADER_LOADER_H_INCLUDED

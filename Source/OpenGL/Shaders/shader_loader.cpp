#include "shader_loader.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

namespace GL
{
    namespace Shader
    {
        std::string getSource ( const std::string& filePath );

        GLuint compileShader ( const GLchar* source, GLenum type );

        GLuint createProgram ( GLuint vertexId, GLuint fragmentId );

        void checkForErrors  ( GLuint id, GLenum status, const std::string& errorType );


        GLuint load ( const std::string& vertexFilePath,
                      const std::string& fragmentFilePath )
        {
            std::string c_vertexSource    = getSource ( vertexFilePath );
            std::string c_fragmentSource  = getSource ( fragmentFilePath );

            GLuint vertexId   = compileShader( c_vertexSource.c_str(),   GL_VERTEX_SHADER   );
            GLuint fragmentId = compileShader( c_fragmentSource.c_str(), GL_FRAGMENT_SHADER );

            GLuint program = createProgram( vertexId, fragmentId );

            glDeleteShader ( vertexId );
            glDeleteShader ( fragmentId );

            return program;
        }

        //Reads the file and converts to a GLchar* for OpenGL to use
        std::string getSource ( const std::string& filePath )
        {
            std::ifstream inFile;
            inFile.exceptions ( std::ifstream::badbit );
            inFile.open( filePath );
            if ( !inFile.is_open() )
            {
                throw std::runtime_error ( "Unable to open " + filePath );
            }

            std::string source;
            try
            {
                 inFile.open( filePath );
                 std::stringstream stream;
                 stream << inFile.rdbuf();
                 source = stream.str();
            }
            catch ( std::ifstream::failure e )
            {
                throw std::runtime_error ("Failed to read shader! " + filePath );
            }

            return source;
        }

        //Compiles the shader and checks if there are any errors in .glsl file
        GLuint compileShader ( const GLchar* source, GLenum type )
        {
            GLuint id;

            id = glCreateShader ( type );
            glShaderSource  ( id, 1, &source, NULL );
            glCompileShader ( id );

            checkForErrors( id, GL_COMPILE_STATUS, "Error compiling shader of type " + type );
            return id;
        }

        //Creates the shader ID
        GLuint createProgram ( GLuint vertexId, GLuint fragmentId )
        {
            GLuint program = glCreateProgram();
            glAttachShader ( program, vertexId   );
            glAttachShader ( program, fragmentId );
            glLinkProgram  ( program );

            checkForErrors( program, GL_LINK_STATUS, "Error linking shaders." );

            return program;
        }

        //Checks for errors and prints them + throws an exception if one is found
        void checkForErrors ( GLuint id, GLenum status, const std::string& errorType )
        {
            GLint success;
            GLchar infoLog[512];

            glGetShaderiv ( id, status, &success );
            if ( !success )
            {
                glGetShaderInfoLog (id, 512, NULL, infoLog );
                throw std::runtime_error ( errorType + "\n" + infoLog  );
            }
        }


    }

}

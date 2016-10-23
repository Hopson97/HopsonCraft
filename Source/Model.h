#ifndef MODEL_H
#define MODEL_H

#include "OpenGL/GLEW/glew.h"

#include <vector>

class Model
{
    public:
        Model   (const std::vector<GLfloat>& vertexCoords, const std::vector<GLfloat>& textureCoords);
        Model   () = default;
        ~Model  ();

        void create (const std::vector<GLfloat>& vertexCoords, const std::vector<GLfloat>& textureCoords);

        void bind () const;
        GLuint getVertexCount () const;

    private:
        void createVBO (GLuint& vbo, GLuint location, GLuint vertexSize, const std::vector<GLfloat>& data );
        void deleteObjects ();

        GLuint m_vao = 0;
        GLuint m_vertexCoords  = 0;
        GLuint m_textureCoords = 0;

        GLuint m_vertexCount = 0;
};

#endif // MODEL_H

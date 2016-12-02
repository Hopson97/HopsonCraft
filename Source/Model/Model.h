#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include <vector>

class Model
{
    public:
        Model   () = default;

        void addData (const std::vector<GLfloat>& vertexCoords,
                      const std::vector<GLfloat>& textureCoords,
                      const std::vector<GLuint>& indices);

        void bind   () const;
        void unbind () const;

        GLuint getIndicesCount () const;

        void addVBO (GLuint vertexSize, const std::vector<GLfloat>& data);

        ~Model  ();
    private:
        void addEBO (const std::vector<GLuint>& indices);

        void deleteBuffers ();

        std::vector<GLuint> m_buffers;
        GLuint m_vao            = 0;
        GLuint m_indicesCount   = 0;
        GLuint m_vboCount       = 0;
};

#endif //MODEL_H

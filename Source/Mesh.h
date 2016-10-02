#ifndef MESH_H
#define MESH_H

#include "OpenGL/GLEW/glew.h"
#include "OpenGL/GLM/glm_transformations.h"

class Mesh
{
    public:
        Mesh() = default;
        Mesh ( GLuint vao, GLuint count, GLuint vert, GLuint txr );

        GLuint getVAO           () const;
        GLuint getVertexCount   () const;

        Vector3 pos;
        Vector3 rot;
        Vector3 sca = { 1, 1, 1 };

        ~Mesh();

        GLuint m_count;

    private:
        GLuint m_vao;

        GLuint m_vert;
        GLuint m_txr;
};

#endif // MESH_H

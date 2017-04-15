#ifndef RINFO_H_INCLUDED
#define RINFO_H_INCLUDED

namespace Renderer
{
    struct Info
    {
        Info(GLuint vaoID, GLuint indices)
        :   vao         (vaoID)
        ,   indexCount  (indices) {}

        GLuint vao;
        GLuint indexCount;
    };
}

#endif // RINFO_H_INCLUDED

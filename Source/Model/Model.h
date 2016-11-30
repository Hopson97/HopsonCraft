#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include <vector>

struct Model_Data
{
    Model_Data () = default;
    Model_Data (    GLuint vao,
                    GLuint vertexPosId,
                    GLuint uvCoordsId,
                    GLuint eboId,
                    size_t indicesCount );

    GLuint vao          = 0;
    GLuint vertexPosId  = 0;
    GLuint uvCoordsId   = 0;

    GLuint eboId          = 0;

    size_t indicesCount = 0;
};

class Model
{
    public:
        Model   () = default;
        Model   (const Model_Data& data);

        void addData (const std::vector<GLfloat>& vertexCoords,
                      const std::vector<GLfloat>& textureCoords,
                      const std::vector<GLuint>& indices);

        void bind   () const;
        void unbind () const;


        GLuint getVertexCount () const;

        ~Model  ();

    private:
        void deleteData ();

        Model_Data m_glData;
};

#endif //MODEL_H

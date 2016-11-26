#ifndef CHUNK_MODEL_H_INCLUDED
#define CHUNK_MODEL_H_INCLUDED

#include "Model.h"

struct Chunk_Model_Data
{
    Chunk_Model_Data () = default;
    Chunk_Model_Data (GLuint vao,
                      GLuint vertexPosId,
                      GLuint uvCoordsId,
                      GLuint lightId,
                      GLuint eboId,
                      size_t indicesCount);

    GLuint vao          = 0;
    GLuint vertexPosId  = 0;
    GLuint uvCoordsId   = 0;
    GLuint lightID      = 0;

    GLuint eboId          = 0;

    size_t indicesCount = 0;
};

class Chunk_Model
{
    public:
        Chunk_Model   () = default;

        void addData (const std::vector<GLfloat>& vertexCoords,
                      const std::vector<GLfloat>& textureCoords,
                      const std::vector<GLfloat>& colour,
                      const std::vector<GLuint>& indices);

        void bind   () const;
        void unbind () const;

        GLuint getVertexCount () const;

        ~Chunk_Model  ();

    private:
        void deleteData ();

         Chunk_Model_Data m_glData;
};

#endif // CHUNK_MODEL_H_INCLUDED

#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <GL/glew.h>

#include <vector>

class Model
{
    public:
        Model() = default;
        Model(const std::vector<GLfloat>& vertexPositions,
              const std::vector<GLfloat>& textureCoordinates,
              const std::vector<GLuint>&  indices);

        ~Model();
        Model(const Model& other) = delete;
        Model& operator =(const Model& other) = delete;

        Model(Model&& other);
        Model& operator =(Model&& other);

        void addData(const std::vector<GLfloat>& vertexPositions,
                     const std::vector<GLfloat>& textureCoordinates,
                     const std::vector<GLuint>&  indices);

        void addVBO(int dim, const std::vector<GLfloat>& data);

        void bind() const;
        void unbind() const;

        GLuint getVAO() const;

        GLuint getIndicesCount() const;

    private:
        void deleteData();

        void addEBO(const std::vector<GLuint>& indices);

        GLuint m_vao = 0;
        GLuint m_vboCount = 0;
        GLuint m_indicesCount = 0;

        std::vector<GLuint> m_buffers;
};



#endif // MODEL_H_INCLUDED

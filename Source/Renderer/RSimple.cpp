
#include "RSimple.h"
#include "../Temp/Quad.h"
#include "../Maths/Matrix_Maths.h"
#include "../Maths/Matrix_Maths.h"

#include "../World/Block/Block_Database.h"

#include "../Camera.h"

namespace Renderer
{
namespace
{
    std::vector<GLfloat> vertexPositions =
    {
        //Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,

        //Right-Side
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,

        //Front
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        //Left
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,

        //Top
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,

        //Bottom
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };


    std::vector<GLuint> indices =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    std::vector<GLfloat> textureCoords;

    void insertTextureCoords(const std::vector<GLfloat>& coords)
    {
        textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    }
}

    RSimple::RSimple()
    {
        auto& textureAtlas = Block::Database::get().getTextureAtlas();
        insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
        insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
        insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
        insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
        insertTextureCoords(textureAtlas.getTextureCoords({0, 0}));
        insertTextureCoords(textureAtlas.getTextureCoords({2, 0}));

        m_cubeModel.addData(vertexPositions, textureCoords, indices);
    }


    void RSimple::draw(const Quad& quad)
    {
        m_quads.push_back(&quad);
    }

    void RSimple::update(const Camera& camera)
    {
        m_shader.bind();

        m_shader.setProjViewMatrix(camera.getProjectionViewMatrix());

        m_cubeModel.bind();

        for (auto& quad : m_quads)
        {
            prepare(*quad);
            glDrawElements(GL_TRIANGLES, m_cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        m_quads.clear();
    }

    void RSimple::prepare(const Quad& quad)
    {
        m_shader.setModelMatrix(Maths::createModelMatrix(quad));

    }
}


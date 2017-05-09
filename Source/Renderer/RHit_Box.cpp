#include "RHit_Box.h"


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
    constexpr float size = 0.1;

    std::vector<GLfloat> vertexPositions =
    {
        //Back
        1 + size,   -size,      -size,
        -size,      -size,      -size,
        -size,      1 + size,   -size,
        1 + size,   1 + size,   -size,

        //Right-Side
        1 + size, -size,    1 + size,
        1 + size, -size,    -size,
        1 + size, 1 + size, -size,
        1 + size, 1 + size, 1 + size,

        //Front
        -size,      -size,      1 + size,
        1 + size,   -size,      1 + size,
        1 + size,   1 + size,   1 + size,
        -size,      1 + size,   1 + size,

        //Left
        -size, -size,       -size,
        -size, -size,       1 + size,
        -size, 1 + size,    1 + size,
        -size, 1 + size,    -size,

        //Top
        -size,      1 + size, 1 + size,
        1 + size,   1 + size, 1 + size,
        1 + size,   1 + size, -size,
        -size,      1 + size, -size,

        //Bottom
        -size,      -size, -size,
        1 + size,   -size, -size,
        1 + size,   -size, 1 + size,
        -size,      -size, 1
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

    RHit_Box::RHit_Box()
    {
        Texture::Atlas* textureAtlas = &Block::Database::get().textures;
        insertTextureCoords(textureAtlas->getTextureCoords({1, 1}));
        insertTextureCoords(textureAtlas->getTextureCoords({1, 1}));
        insertTextureCoords(textureAtlas->getTextureCoords({1, 1}));
        insertTextureCoords(textureAtlas->getTextureCoords({1, 1}));
        insertTextureCoords(textureAtlas->getTextureCoords({1, 1}));
        insertTextureCoords(textureAtlas->getTextureCoords({1, 1}));

        m_cubeModel.addData(vertexPositions, textureCoords, indices);
    }


    void RHit_Box::draw(const Vector3& location)
    {
        m_nextDrawLocation = location;
    }

    void RHit_Box::update(const Camera& camera)
    {
        if (m_nextDrawLocation == Vector3{-1, -1, -1}) return;

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        m_shader.bind();
        m_cubeModel.bind();

        m_shader.setProjViewMatrix(camera.getProjectionViewMatrix());
        m_shader.setModelMatrix(Maths::createModelMatrix({m_nextDrawLocation,
                                                         {0, 0, 0}}));


        glDrawElements(GL_TRIANGLES,
                       m_cubeModel.getIndicesCount(),
                       GL_UNSIGNED_INT,
                       nullptr);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_nextDrawLocation = {-1, -1, -1};
    }
}


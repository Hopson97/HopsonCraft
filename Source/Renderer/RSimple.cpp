
#include "RSimple.h"
#include "../Entity/Cube.h"
#include "../Maths/Matrix_Maths.h"
#include "../Maths/Matrix_Maths.h"

#include "../World/Block/Block_Database.h"

#include "../Camera.h"

#include "../Model_Coords.h"


namespace Renderer
{
namespace
{
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

        m_cubeModel.addData(getCubeVerticies(0.0f), textureCoords, getCubeIndices());
    }


    void RSimple::draw(const Cube& cube)
    {
        m_cubes.push_back(&cube);
    }

    void RSimple::update(const Camera& camera)
    {
        m_shader.bind();

        m_shader.setProjViewMatrix(camera.getProjectionViewMatrix());

        m_cubeModel.bind();

        for (auto& cube : m_cubes)
        {
            prepare(*cube);
            glDrawElements(GL_TRIANGLES, m_cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        m_cubes.clear();
    }

    void RSimple::prepare(const Cube& cube)
    {
        m_shader.setModelMatrix(Maths::createModelMatrix(cube));

    }
}


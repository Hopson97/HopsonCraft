#include "SimpleRenderer.h"

#include "../Entity/Cube.h"
#include "../Maths/Matrix.h"
#include "../Maths/Matrix.h"

#include "../World/Block/BlockDatabase.h"

#include "../Camera.h"

#include "../ModelCoords.h"


namespace
{
    std::vector<GLfloat> textureCoords;

    void insertTextureCoords(const std::vector<GLfloat>& coords)
    {
        textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    }
}

SimpleRenderer::SimpleRenderer()
{
    auto& textureAtlas = BlockDatabase::get().getTextureAtlas();
    insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
    insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
    insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
    insertTextureCoords(textureAtlas.getTextureCoords({1, 0}));
    insertTextureCoords(textureAtlas.getTextureCoords({0, 0}));
    insertTextureCoords(textureAtlas.getTextureCoords({2, 0}));

    m_cubeModel.addData(getCubeVerticies(0.5f), textureCoords, getCubeIndices());
}


void SimpleRenderer::draw(const Cube& cube)
{
    m_cubes.push_back(&cube);
}

void SimpleRenderer::update(const Camera& camera)
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

void SimpleRenderer::prepare(const Cube& cube)
{
    m_shader.setModelMatrix(createModelMatrix(cube));

}

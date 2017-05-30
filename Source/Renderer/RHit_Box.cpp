#include "RHit_Box.h"


#include "RSimple.h"
#include "../Temp/Quad.h"
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

    RHit_Box::RHit_Box()
    {
        auto& textureAtlas = Block::Database::get().getTextureAtlas();
        auto coords = textureAtlas.getTextureCoords({1, 1});
        insertTextureCoords(coords);
        insertTextureCoords(coords);
        insertTextureCoords(coords);
        insertTextureCoords(coords);
        insertTextureCoords(coords);
        insertTextureCoords(coords);

        m_cubeModel.addData(getCubeVerticies(0.1f), textureCoords, getCubeIndices());
    }


    void RHit_Box::draw(const Vector3& location)
    {
        m_nextDrawLocation = location;
    }

    void RHit_Box::update(const Camera& camera)
    {
        if (m_nextDrawLocation == Vector3{-1, -1, -1}) return;

        glDisable(GL_CULL_FACE);

        m_shader.bind();
        m_cubeModel.bind();

        m_shader.setProjViewMatrix(camera.getProjectionViewMatrix());
        m_shader.setModelMatrix(Maths::createModelMatrix({m_nextDrawLocation,
                                                         {0, 0, 0}}));


        glDrawElements(GL_LINES,
                       m_cubeModel.getIndicesCount(),
                       GL_UNSIGNED_INT,
                       nullptr);


        m_nextDrawLocation = {-1, -1, -1};
    }
}


#include "RChunk.h"

#include <iostream>

#include "../World/Chunk/Chunklet.h"
#include "../Maths/Matrix_Maths.h"
#include "../World/Chunk/Chunklet.h"

namespace Renderer
{
    void RChunk::draw(const Chunklet& chunklet)
    {
        m_chunks.push_back(&chunklet);
    }

    void RChunk::update(const Camera& camera)
    {
        //glEnable    (GL_CULL_FACE);

        m_shader.bind();

        m_shader.setViewMatrix(Maths::createViewMatrix(camera));

        for (const Chunklet* chunklet : m_chunks)
        {/*
            if(chunklet->getPosition().x == 0 &&
               chunklet->getPosition().z == 0 )
            {
                std::cout << "Center\n" << " " << chunklet->getMesh().getSolidMesh().getIndicesCount() << "\n";
            }*/

            prepare(*chunklet);
            glDrawElements(GL_TRIANGLES,
                           chunklet->getMesh().getSolidMesh().getModel().getIndicesCount(),
                           GL_UNSIGNED_INT,
                           nullptr);
        }
        m_chunks.clear();
    }

    void RChunk::prepare(const Chunklet& chunklet)
    {
        chunklet.getMesh().getSolidMesh().getModel().bind();
        m_shader.setModelMatrix(chunklet.getMat());

    }
}

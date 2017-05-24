#include "Mesh.h"

#include "../World_Constants.h"

#include <SFML/Graphics.hpp>

namespace
{
    template<typename T>
    void clearMemory(std::vector<T>& vect)
    {
        vect.clear();
        vect.shrink_to_fit();
    }
}

namespace Chunk
{
    void Mesh::reset()
    {
        m_indicesIndex = 0;
        m_facesCount   = 0;
    }

    void Mesh::addFace(  const std::vector<GLfloat>&    templateFace,
                         const std::vector<GLfloat>&    texCoords,
                         const sf::Vector3<GLfloat>&    light,
                         const Chunklet_Position&       chunkPos,
                         const Block::Position&         localPosition)
    {
        ++m_facesCount;

        //Builds the vertex positions of the mesh, one vertex (3D) at a time of the face passed in
        //Does this 4 times for each of the 4 vertices that makes up a block face
        for (int i = 0, index = 0; i < 4; ++i)
        {
            m_verticies.push_back(templateFace[index++] + chunkPos.x * CHUNK_SIZE + localPosition.x);
            m_verticies.push_back(templateFace[index++] + chunkPos.y * CHUNK_SIZE + localPosition.y);
            m_verticies.push_back(templateFace[index++] + chunkPos.z * CHUNK_SIZE + localPosition.z);
        }

        m_texCoords.insert(m_texCoords.end(), texCoords.begin(), texCoords.end());

        for (int i = 0; i < 4; ++i)
        {
            m_lights.push_back(light.x);
            m_lights.push_back(light.y);
            m_lights.push_back(light.z);
        }

        m_indices.insert(m_indices.end(),
        {
            m_indicesIndex,
            m_indicesIndex + 1,
            m_indicesIndex + 2,
            m_indicesIndex + 2,
            m_indicesIndex + 3,
            m_indicesIndex
        });
        m_indicesIndex += 4;
    }

    void Mesh::buffer()
    {
        m_model.addData(m_verticies, m_texCoords, m_indices);
        m_model.addVBO(3, m_lights);

        //Clear up some memory, also prevents odd stuff happening for mesh rebuild
        clearMemory(m_verticies);
        clearMemory(m_texCoords);
        clearMemory(m_indices);
        clearMemory(m_lights);
    }

    const Model& Mesh::getModel() const
    {
        return m_model;
    }

    uint32_t Mesh::getFaceCount() const
    {
        return m_facesCount;
    }


}

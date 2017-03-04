#include "CMesh.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../World_Constants.h"

#include "../Block/Block_Database.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

#include "Chunklet.h"

namespace Chunk
{
    namespace
    {
        constexpr GLfloat   LIGHT_TOP       =   1.0,
                            LIGHT_Z         =   0.82f,
                            LIGHT_X         =   0.7,
                            LIGHT_BOTTOM    =   0.5;
    }

    void Mesh::Section::reserve()
    {
        m_verticies.reserve (40000);
        m_texCoords.reserve (20000);
        m_indices.reserve   (10000);
        m_light.reserve     (10000);
    }

    void Mesh::Section::buffer()
    {
        m_model.addData(m_verticies, m_texCoords, m_indices);
        m_model.addVBO(1, m_light);

        m_verticies .clear();
        m_texCoords .clear();
        m_indices   .clear();
        m_light     .clear();

        m_verticies .shrink_to_fit();
        m_texCoords .shrink_to_fit();
        m_indices   .shrink_to_fit();
        m_light     .shrink_to_fit();

    }

    void Mesh::Section::addVerticies(const std::vector<GLfloat>& v)
    {
        m_verticies.insert(m_verticies.end(), v.begin(), v.end());
    }

    void Mesh::Section::addTexCoords(const std::vector<GLfloat>& t)
    {
        m_texCoords.insert(m_texCoords.end(), t.begin(), t.end());
    }

    void Mesh::Section::addIndices(const std::vector<GLuint>& i)
    {
        m_indices.insert(m_indices.end(), i.begin(), i.end());
    }

    void Mesh::Section::addLightVal(GLfloat cardinalVal)
    {
        m_light.insert(m_light.end(), {cardinalVal, cardinalVal, cardinalVal, cardinalVal});
    }


    GLuint Mesh::Section::getIndicesCount() const
    {
        return m_indicesCount;
    }

    void Mesh::Section::addToIndexCount(GLuint amount)
    {
        m_indicesCount += amount;
    }

    const Model& Mesh::Section::getModel() const
    {
        return m_model;
    }


    Mesh::Mesh(Chunklet& chunklet)
    :   m_p_chunklet        (&chunklet)
    ,   m_p_textureAtlas    (&Block::Database::get().textures)
    { }

    void Mesh::create()
    {
        //sf::Clock timer;
        uint32_t faces = 0;

        //m_solidMesh.reserve();

        for (int8_t y = 0; y < World_Constants::CH_SIZE; ++y){
            for (int8_t x = 0; x < World_Constants::CH_SIZE; ++x){
                for (int8_t z = 0; z < World_Constants::CH_SIZE; ++z)
                {
                    Block::Small_Position pos{x, y, z};
                    if (m_p_chunklet->qGetBlock(pos) == Block::ID::Air)
                    {
                        continue;
                    }
                    else
                    {
                        m_p_activeBlockData = &Block::Database::get().
                                                getBlock(m_p_chunklet->qGetBlock(pos).id).getData();

                        //ugly C++ casts be like
                        if (shouldMakeFaceAdjacentTo({x, static_cast<int8_t>(y + 1), z}))
                        {
                            makeTopFace (pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({x, static_cast<int8_t>(y - 1), z}))
                        {
                            makeBottomFace(pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<int8_t>(x - 1), y, z}))
                        {
                            makeLeftFace (pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<int8_t>(x + 1), y, z}))
                        {
                            makeRightFace (pos);
                            ++faces;
                        }
                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<int8_t>(z + 1)}))
                        {
                            makeFrontFace (pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<int8_t>(z - 1)}))
                        {
                            makeBackFace (pos);
                            ++faces;
                        }
                    }
                }
            }
        }

        for (uint32_t i = 0; i < faces; ++i)
        {
            auto count = m_solidMesh.getIndicesCount();

            m_solidMesh.addIndices(
            {
                count,
                count + 1,
                count + 2,
                count + 2,
                count + 3,
                count,
            });

            m_solidMesh.addToIndexCount(4);
        }


        m_p_chunklet->setFaces(faces);
        //std::cout << faces << " faces added in " << timer.getElapsedTime().asSeconds() << " seconds.\n";
    }

    void Mesh::buffer() { m_solidMesh.buffer(); }

    const Mesh::Section& Mesh::getSolidMesh() const { return m_solidMesh; }


    bool Mesh::shouldMakeFaceAdjacentTo(const Block::Small_Position& pos)
    {
        CBlock block = m_p_chunklet->getBlock(pos);
        return block == Block::ID::Air;
    }

    void Mesh::makeFrontFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_solidMesh.addVerticies(
        {
            x,      y,      z + 1,
            x + 1,  y,      z + 1,
            x + 1,  y + 1,  z + 1,
            x,      y + 1,  z + 1,
        });

        m_solidMesh.addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->getSideTex()));

        m_solidMesh.addLightVal(LIGHT_Z);
    }

    void Mesh::makeBackFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_solidMesh.addVerticies(
        {
            x + 1,  y,      z,
            x,      y,      z,
            x,      y + 1,  z,
            x + 1,  y + 1,  z,
        });

        m_solidMesh.addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->getSideTex()));

        m_solidMesh.addLightVal(LIGHT_Z);
    }

    void Mesh::makeLeftFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_solidMesh.addVerticies(
        {
            x, y,       z,
            x, y,       z + 1,
            x, y + 1,   z + 1,
            x, y + 1,   z,
        });

        m_solidMesh.addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->getSideTex()));

        m_solidMesh.addLightVal(LIGHT_X);
    }

    void Mesh::makeRightFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_solidMesh.addVerticies(
        {
            x + 1, y,       z + 1,
            x + 1, y,       z,
            x + 1, y + 1,   z,
            x + 1, y + 1,   z + 1,
        });

        m_solidMesh.addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->getSideTex()));

        m_solidMesh.addLightVal(LIGHT_X);
    }

    void Mesh::makeTopFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_solidMesh.addVerticies(
        {
            x,      y + 1, z + 1,   //Front-Left
            x + 1,  y + 1, z + 1,   //Front-Right
            x + 1,  y + 1, z,       //Back-Right
            x,      y + 1, z,       //Back-Left
        });

        m_solidMesh.addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->getTopTex()));

        m_solidMesh.addLightVal(LIGHT_TOP);
    }

    void Mesh::makeBottomFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_solidMesh.addVerticies(
        {
            x,      y, z,
            x + 1,  y, z,
            x + 1,  y, z + 1,
            x,      y, z + 1,
        });

        m_solidMesh.addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->getBottomTex()));

        m_solidMesh.addLightVal(LIGHT_BOTTOM);
    }
}


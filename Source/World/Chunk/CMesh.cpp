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
    void Mesh::Section::reserve()
    {
        m_verticies.reserve   (61440);
        m_texCoords.reserve   (40960);
        m_indices.reserve     (30720);
    }

    void Mesh::Section::buffer()
    {
        m_model.addData(m_verticies, m_texCoords, m_indices);

        m_verticies.clear();
        m_texCoords.clear();
        m_indices.clear();

        m_verticies.shrink_to_fit();
        m_verticies.shrink_to_fit();
        m_verticies.shrink_to_fit();
    }

    inline void Mesh::Section::addVerticies(const std::vector<GLfloat>& v)
    {
        m_verticies.insert(m_verticies.end(), v.begin(), v.end());
    }

    inline void Mesh::Section::addTexCoords(const std::vector<GLfloat>& t)
    {
        m_texCoords.insert(m_texCoords.end(), t.begin(), t.end());
    }

    inline void Mesh::Section::addIndices(const std::vector<GLuint>& i)
    {
        m_indices.insert(m_indices.end(), i.begin(), i.end());
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


    Mesh::Mesh(const Chunklet& chunklet)
    :   m_p_chunklet        (&chunklet)
    ,   m_p_textureAtlas    (&Block::Database::get().textures)
    { }

    void Mesh::create()
    {
        sf::Clock timer;
        uint32_t faces = 0;

        m_solidMesh.reserve();

        for (uint8_t y = 0; y < World_Constants::CH_SIZE; ++y){
            for (uint8_t x = 0; x < World_Constants::CH_SIZE; ++x){
                for (uint8_t z = 0; z < World_Constants::CH_SIZE; ++z)
                {
                    Block::Position pos{x, y, z};
                    if (m_p_chunklet->getBlock(pos) == Block::ID::Air)
                    {
                        continue;
                    }
                    else
                    {
                        m_p_activeBlockData = &Block::Database::get().
                                                getBlock(m_p_chunklet->getBlock(pos).id).getData();

                        //ugly C++ casts be like
                        if (shouldMakeFaceAdjacentTo({x, static_cast<uint8_t>(y + 1), z}))
                        {
                            makeTopFace (pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({x, static_cast<uint8_t>(y - 1), z}) && y != 0)
                        {
                            makeBottomFace(pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<uint8_t>(x - 1), y, z}))
                        {
                            makeLeftFace (pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<uint8_t>(x + 1), y, z}))
                        {
                            makeRightFace (pos);
                            ++faces;
                        }
                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<uint8_t>(z + 1)}))
                        {
                            makeFrontFace (pos);
                            ++faces;
                        }

                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<uint8_t>(z - 1)}))
                        {
                            makeBackFace (pos);
                            ++faces;
                        }
                    }
                }
            }
        }
        addIndices(faces);
        m_solidMesh.buffer();

        //smh all this white space
        std::cout << "Faces: " << faces << " took " << timer.getElapsedTime().asSeconds() << " to make.\n";
    }

    const Mesh::Section& Mesh::getSolidMesh() const
    {
        return m_solidMesh;
    }


    bool Mesh::shouldMakeFaceAdjacentTo(const Block::Position& pos)
    {
        CBlock block = m_p_chunklet->getBlock(pos);


        return block == Block::ID::Air;
    }

    void Mesh::makeFrontFace(const Block::Position& pos)
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
    }

    void Mesh::makeBackFace(const Block::Position& pos)
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
    }

    void Mesh::makeLeftFace(const Block::Position& pos)
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
    }

    void Mesh::makeRightFace(const Block::Position& pos)
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
    }

    void Mesh::makeTopFace(const Block::Position& pos)
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
    }

    void Mesh::makeBottomFace(const Block::Position& pos)
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
    }

    void Mesh::addIndices(uint32_t faces)
    {
        for (uint32_t i = 0; i < faces; ++i)
        {
            auto count = m_solidMesh.getIndicesCount();

            m_solidMesh.addIndices(
            {
                0 + count,
                1 + count,
                2 + count,
                2 + count,
                3 + count,
                0 + count,
            });

            m_solidMesh.addToIndexCount(4);
        }
    }


}


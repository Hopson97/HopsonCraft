#include "CMesh.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../World_Constants.h"

#include "../Block/Block_Database.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

#include "Chunklet.h"
/*
namespace
{
    std::vector<GLfloat> cubeCoords
    {
        0, 0, 0, //0    Left,   bottom, back
        1, 0, 0, //1    Right,
        1, 1, 0, //2
        1, 0, 1, //3
        0, 1, 0, //4
        0, 1, 1, //5
        0, 0, 1, //6
        1, 1, 1, //7
    };
}
*/
namespace Chunk
{
    namespace
    {
        constexpr GLfloat   LIGHT_TOP       =   1.0,
                            LIGHT_Z         =   0.7,
                            LIGHT_X         =   0.5,
                            LIGHT_BOTTOM    =   0.3;
    }

    void Mesh_Section::reserve(size_t vert, size_t tex, size_t ind, size_t light)
    {
        m_verticies.reserve (vert);
        m_texCoords.reserve (tex);
        m_indices.reserve   (ind);
        m_light.reserve     (light);
    }


    void Mesh_Section::reset()
    {
        m_faces = 0;
        m_indicesIndex = 0;
    }

    void Mesh_Section::buffer()
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



    void Mesh_Section::addVerticies(const std::vector<GLfloat>& v)
    {
        m_faces++;
        m_verticies.insert(m_verticies.end(), v.begin(), v.end());
    }

    void Mesh_Section::addTexCoords(const std::vector<GLfloat>& t)
    {
        m_texCoords.insert(m_texCoords.end(), t.begin(), t.end());
    }

    void Mesh_Section::addIndices(const std::vector<GLuint>& i)
    {
        m_indices.insert(m_indices.end(), i.begin(), i.end());
    }

    void Mesh_Section::addLightVal(GLfloat cardinalVal)
    {
        m_light.insert(m_light.end(), {cardinalVal, cardinalVal, cardinalVal, cardinalVal});
    }

    const Model& Mesh_Section::getModel() const
    {
        return m_model;
    }


    void Mesh_Section::addIndices()
    {
        addIndices(
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




    Mesh::Mesh(Chunklet& chunklet)
    :   m_p_chunklet        (&chunklet)
    ,   m_p_textureAtlas    (&Block::Database::get().textures)
    { }

    void Mesh::create()
    {
        sf::Clock timer;

        m_solidMesh.reset();
        m_liquidMesh.reset();

        m_liquidMesh.reserve(World_Constants::CH_AREA * 12,
                             World_Constants::CH_AREA * 8,
                             World_Constants::CH_AREA * 4,
                             World_Constants::CH_AREA * 4);

        for (int8_t y = 0; y < World_Constants::CH_SIZE; ++y){
            for (int8_t x = 0; x < World_Constants::CH_SIZE; ++x){
                for (int8_t z = 0; z < World_Constants::CH_SIZE; ++z)
                {
                    if (m_p_chunklet->qGetBlock({x, y, z}) == Block::ID::Air)
                    {
                        continue;
                    }
                    else
                    {
                        auto chunkPos = m_p_chunklet->getPosition();

                        GLfloat minX = x + chunkPos.x * World_Constants::CH_SIZE;
                        GLfloat minY = y + chunkPos.y * World_Constants::CH_SIZE;
                        GLfloat minZ = z + chunkPos.z * World_Constants::CH_SIZE;


                        GLfloat maxX = x + chunkPos.x * World_Constants::CH_SIZE + 1;
                        GLfloat maxY = y + chunkPos.y * World_Constants::CH_SIZE + 1;
                        GLfloat maxZ = z + chunkPos.z * World_Constants::CH_SIZE + 1;

                        Vector3 minPosition (minX,
                                             minY,
                                             minZ);

                        Vector3 maxPosition (maxX,
                                             maxY,
                                             maxZ);



                        m_p_activeBlockData = &Block::Database::get().
                                                getBlock(m_p_chunklet->qGetBlock({x, y, z}).id).getData();

                        setActiveSection();

                        if (shouldMakeFaceAdjacentTo({x, static_cast<int8_t>(y + 1), z}))
                        {
                            makeTopFace (minPosition, maxPosition);
                            m_activeSection->addIndices();
                        }

                        if (shouldMakeFaceAdjacentTo({x, static_cast<int8_t>(y - 1), z}))
                        {
                            makeBottomFace(minPosition, maxPosition);
                            m_activeSection->addIndices();
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<int8_t>(x - 1), y, z}))
                        {
                            makeLeftFace (minPosition, maxPosition);
                            m_activeSection->addIndices();
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<int8_t>(x + 1), y, z}))
                        {
                            makeRightFace (minPosition, maxPosition);
                            m_activeSection->addIndices();
                        }
                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<int8_t>(z + 1)}))
                        {
                            makeFrontFace (minPosition, maxPosition);
                            m_activeSection->addIndices();
                        }

                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<int8_t>(z - 1)}))
                        {
                            makeBackFace (minPosition, maxPosition);
                            m_activeSection->addIndices();
                        }
                    }
                }
            }
        }
        m_p_chunklet->setFaces(m_solidMesh .getFacesCount() |
                               m_liquidMesh.getFacesCount());
    }

    void Mesh::setActiveSection()
    {
        switch(m_p_activeBlockData->get().meshType)
        {
            case Block::Mesh_Type::Solid:
                m_activeSection = &m_solidMesh;
                break;

            case Block::Mesh_Type::Liquid:
                m_activeSection = &m_liquidMesh;
                break;
        }
    }

    void Mesh::buffer()
    {
        m_solidMesh.buffer();
        m_liquidMesh.buffer();
    }

    const Mesh_Section& Mesh::getSolidMesh() const
    {
        return m_solidMesh;
    }

    const Mesh_Section& Mesh::getLiquidMesh() const
    {
        return m_liquidMesh;
    }


    bool Mesh::shouldMakeFaceAdjacentTo(const Block::Small_Position& pos)
    {
        CBlock block = m_p_chunklet->getBlock(pos);
        const Block::Data_Holder& adjacentBlockData = Block::Database::get().getBlock(block.id).getData().get();

        if (block == Block::ID::Air)
        {
            return true;
        }
        else if ( adjacentBlockData.blockID == m_p_activeBlockData->get().blockID)
        {
            return false;
        }
        else if (!adjacentBlockData.isOpaque)
        {
            return true;
        }
        return false;
    }

    void Mesh::makeFrontFace(const Vector3& min, const Vector3& max)
    {
        m_activeSection->addVerticies(
        {
            min.x,  min.y,  max.z,
            max.x,  min.y,  max.z,
            max.x,  max.y,  max.z,
            min.x,  max.y,  max.z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                      getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_Z);
    }

    void Mesh::makeBackFace(const Vector3& min, const Vector3& max)
    {
        m_activeSection->addVerticies(
        {
            max.x,  min.y,  min.z,
            min.x,  min.y,  min.z,
            min.x,  max.y,  min.z,
            max.x,  max.y,  min.z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_Z);
    }

    void Mesh::makeLeftFace(const Vector3& min, const Vector3& max)
    {
        m_activeSection->addVerticies(
        {
            min.x, min.y,   min.z,
            min.x, min.y,   max.z,
            min.x, max.y,   max.z,
            min.x, max.y,   min.z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_X);
    }

    void Mesh::makeRightFace(const Vector3& min, const Vector3& max)
    {
        m_activeSection->addVerticies(
        {
            max.x, min.y,   max.z,
            max.x, min.y,   min.z,
            max.x, max.y,   min.z,
            max.x, max.y,   max.z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_X);
    }

    void Mesh::makeTopFace(const Vector3& min, const Vector3& max)
    {
        m_activeSection->addVerticies(
        {
            min.x,  max.y, max.z,   //Front-Left
            max.x,  max.y, max.z,   //Front-Right
            max.x,  max.y, min.z,       //Back-Right
            min.x,  max.y, min.z,       //Back-Left
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().topTextureCoords));

        m_activeSection->addLightVal(LIGHT_TOP);
    }

    void Mesh::makeBottomFace(const Vector3& min, const Vector3& max)
    {
        m_activeSection->addVerticies(
        {
            min.x,  min.y, min.z,
            max.x,  min.y, min.z,
            max.x,  min.y, max.z,
            min.x,  min.y, max.z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().bottomTextureCoords));

        m_activeSection->addLightVal(LIGHT_BOTTOM);
    }
}


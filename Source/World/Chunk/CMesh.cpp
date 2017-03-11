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
                            LIGHT_Z         =   0.7,
                            LIGHT_X         =   0.5,
                            LIGHT_BOTTOM    =   0.3;
    }

    void Mesh_Section::reset()
    {
        m_faces = 0;
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
        for (uint32_t i = 0, count = 0; i < m_faces; ++i, count += 4)
        {
            addIndices(
            {
                count,
                count + 1,
                count + 2,
                count + 2,
                count + 3,
                count,
            });
        }
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

                        setActiveSection();

                        if (shouldMakeFaceAdjacentTo({x, static_cast<int8_t>(y + 1), z}))
                        {
                            makeTopFace (pos);
                        }

                        if (shouldMakeFaceAdjacentTo({x, static_cast<int8_t>(y - 1), z}))
                        {
                            makeBottomFace(pos);
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<int8_t>(x - 1), y, z}))
                        {
                            makeLeftFace (pos);
                        }

                        if (shouldMakeFaceAdjacentTo({static_cast<int8_t>(x + 1), y, z}))
                        {
                            makeRightFace (pos);
                        }
                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<int8_t>(z + 1)}))
                        {
                            makeFrontFace (pos);
                        }

                        if (shouldMakeFaceAdjacentTo({x, y, static_cast<int8_t>(z - 1)}))
                        {
                            makeBackFace (pos);
                        }
                    }
                }
            }
        }


        m_solidMesh.addIndices();
        m_liquidMesh.addIndices();

        m_p_chunklet->setFaces(m_solidMesh.getFacesCount() | m_liquidMesh.getFacesCount());
        //std::cout << " faces added in " << timer.getElapsedTime().asSeconds() << " seconds.\n";
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
        const Block::Data_Holder& d = Block::Database::get().getBlock(block.id).getData().get();

        return  block == Block::ID::Air ||
                (!d.isOpaque && d.blockID != m_p_activeBlockData->get().blockID);
    }

    void Mesh::makeFrontFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_activeSection->addVerticies(
        {
            x,      y,      z + 1,
            x + 1,  y,      z + 1,
            x + 1,  y + 1,  z + 1,
            x,      y + 1,  z + 1,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                      getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_Z);
    }

    void Mesh::makeBackFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_activeSection->addVerticies(
        {
            x + 1,  y,      z,
            x,      y,      z,
            x,      y + 1,  z,
            x + 1,  y + 1,  z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_Z);
    }

    void Mesh::makeLeftFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_activeSection->addVerticies(
        {
            x, y,       z,
            x, y,       z + 1,
            x, y + 1,   z + 1,
            x, y + 1,   z,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_X);
    }

    void Mesh::makeRightFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_activeSection->addVerticies(
        {
            x + 1, y,       z + 1,
            x + 1, y,       z,
            x + 1, y + 1,   z,
            x + 1, y + 1,   z + 1,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().sideTextureCoords));

        m_activeSection->addLightVal(LIGHT_X);
    }

    void Mesh::makeTopFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_activeSection->addVerticies(
        {
            x,      y + 1, z + 1,   //Front-Left
            x + 1,  y + 1, z + 1,   //Front-Right
            x + 1,  y + 1, z,       //Back-Right
            x,      y + 1, z,       //Back-Left
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().topTextureCoords));

        m_activeSection->addLightVal(LIGHT_TOP);
    }

    void Mesh::makeBottomFace(const Block::Small_Position& pos)
    {
        GLfloat x = static_cast<GLfloat>(pos.x);
        GLfloat y = static_cast<GLfloat>(pos.y);
        GLfloat z = static_cast<GLfloat>(pos.z);

        m_activeSection->addVerticies(
        {
            x,      y, z,
            x + 1,  y, z,
            x + 1,  y, z + 1,
            x,      y, z + 1,
        });

        m_activeSection->addTexCoords(m_p_textureAtlas->
                                 getTextureCoords(m_p_activeBlockData->get().bottomTextureCoords));

        m_activeSection->addLightVal(LIGHT_BOTTOM);
    }
}


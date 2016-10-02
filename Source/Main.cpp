#include <SFML/Graphics.hpp>

#include "OpenGL/GLEW/glew.h"
#include "OpenGL/GLM/glm_transformations.h"

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>

#include "Camera.h"
#include "Utilities/Loader.h"
#include "Blocks/Blocks.h"

#include "shader_loader.h"

#include "Chunk/Chunk.h"

#include "Utilities/FPS.h"
#include "Window.h"

struct Chunk_Positions
{
    Chunk_Positions() = default;
    Chunk_Positions ( int xStart,
                      int xEnd,
                      int zStart,
                      int zEnd )
    :   mxStart ( xStart )
    ,   mxEnd   ( xEnd )
    ,   mZStart ( zStart )
    ,   mZEnd   ( zEnd )
    {}

    Chunk_Positions get ( Camera& camera, int size )
    {
        int xStart = camera.getPosition().x - size / 2;
        int xEnd = camera.getPosition().x + size / 2;

        int zStart = camera.getPosition().z - size / 2;
        int zEnd = camera.getPosition().z + size / 2;

        return { xStart, xEnd, zStart, zEnd };
    }
    int mxStart;
    int mxEnd;

    int mZStart;
    int mZEnd;
};



void checkForClose  ( sf::RenderWindow& window );
void clearWindow    ();

Matrix4 createTransforrmationMatrix(const Vector3& translation, const Vector3& rotation, const Vector3& scale)
{
    Matrix4 transformation;

    transformation = glm::translate( transformation, translation );

    transformation = glm::rotate( transformation, glm::radians( rotation.x ), { 1, 0, 0 } );
    transformation = glm::rotate( transformation, glm::radians( rotation.y ), { 0, 1, 0 } );
    transformation = glm::rotate( transformation, glm::radians( rotation.z ), { 0, 0, 1 } );

    transformation = glm::scale( transformation, scale );

    return transformation;
}


Matrix4 createViewMatrix ( const Camera& camera )
{
    Matrix4 view;

    view = glm::rotate     ( view, glm::radians( camera.getRotation().x ), { 1, 0, 0} );
    view = glm::rotate     ( view, glm::radians( camera.getRotation().y ), { 0, 1, 0} );
    view = glm::translate  ( view, -camera.getPosition() );//

    return view;
}

Vector2 getChunkPos ( Camera& cam )
{
    int xPos = cam.getPosition().x / Chunk::WIDTH;
    int zPos = cam.getPosition().z / Chunk::WIDTH;

    return { xPos, zPos };
}

int main()
{
    srand ( time ( NULL ) );

    Height_Generator::setUp( Chunk::HEIGHT / 1.5, 5 );

    Window::create();

    GLuint shader = GL::Shader::load( "Shaders/Vertex.glsl", "Shaders/Fragment.glsl" );
    Camera camera;
    Loader loader;

    GLuint texture = loader.loadTexture( "mc" ); //This is the texture atlas used by all blocks

    int size = 25;
    sf::Clock timer;
    std::vector<std::unique_ptr<Chunk>> m_chunks;
    std::vector<Vector2> chunkPositions;

    Chunk_Positions positions;
    positions = positions.get( camera, size );

    for ( int x = positions.mxStart ; x < positions.mxEnd  ; x++ )
    {
        for ( int z = positions.mZStart ; z < positions.mZEnd ; z++)
        {
            m_chunks.emplace_back ( std::make_unique<Chunk>( loader, x, z ) );
            chunkPositions.push_back( { x, z } );
        }
    }


    size_t blocks = m_chunks.size() * Chunk::WIDTH * Chunk::HEIGHT * Chunk::WIDTH;
    std::cout << "Time for chunk creation: "    << timer.getElapsedTime().asSeconds() << ". Total Chunks: " << m_chunks.size() << std::endl;
    std::cout << "Total \"Blocks\": "           << blocks << std::endl;

    FPS fps;

    Matrix4 pers = glm::perspective( glm::radians( 75.0f ), (float)Window::WIDTH/ (float)Window::HEIGHT, 0.01f, 1000.0f);
    glUseProgram ( shader );
    GLuint projectionLocation   = glGetUniformLocation ( shader, "projectionMatrix" );
    GLuint viewLocation         = glGetUniformLocation ( shader, "viewMatrix"       );
    GLuint modelLocation        = glGetUniformLocation ( shader, "modelMatrix"      );

    glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( pers ) );

    camera.movePosition( {  -4,
                            100,
                            -5 } );
    camera.m_rotation.y += 160;

    Vector2 currentPos = getChunkPos( camera );

    sf::Clock c;

    while ( Window::isOpen() )
    {
        if ( currentPos != getChunkPos( camera ) ) {
            currentPos = getChunkPos( camera );
            std::cout << "CHANGE" << std::endl;
        }

        float dt = c.restart().asSeconds();

        Window::clear();

        glUniformMatrix4fv ( viewLocation, 1, GL_FALSE, glm::value_ptr( createViewMatrix( camera ) ) );

        glActiveTexture ( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );

        camera.move( dt );

        for ( auto& chunk : m_chunks )
        {
            glBindVertexArray ( chunk->tempMesh->getVAO() );
            glUniformMatrix4fv ( modelLocation, 1, GL_FALSE, glm::value_ptr( createTransforrmationMatrix
                                 ( chunk->tempMesh->pos,
                                   chunk->tempMesh->rot,
                                   chunk->tempMesh->sca ) ) );
            glDrawArrays( GL_TRIANGLES, 0, chunk->tempMesh->getVertexCount() );

        }

        Window::checkForClose();

        fps.update();

        //Window::prepareSfDraw();
        //fps.drawFPS();
        //Window::endSfDraw();


        Window::update();
    }


    return 0;
}

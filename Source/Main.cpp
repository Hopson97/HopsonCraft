#include <SFML/Graphics.hpp>

#include "OpenGL/GLEW/glew.h"
#include "OpenGL/GLM/glm_transformations.h"

#include <vector>
#include <iostream>
#include <memory>

#include "Camera.h"
#include "../Loader.h"
#include "Block.h"

#include "shader_loader.h"

#include "Chunk.h"

#include "FPS.h"

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
//
    view = glm::rotate     ( view, glm::radians( camera.getRotation().x ), { 1, 0, 0} );
    view = glm::rotate     ( view, glm::radians( camera.getRotation().y ), { 0, 1, 0} );
    view = glm::translate  ( view, -camera.getPosition() );

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

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    float w = 1280;
    float h = 720;

    sf::RenderWindow window ( sf::VideoMode ( w, h ), "Minecraft Clone Test", sf::Style::Close, settings );

    glewInit();
    glewExperimental = GL_TRUE;
    glViewport  ( 0, 0, w, h );

    glEnable    ( GL_DEPTH_TEST );

    GLuint shader = GL::Shader::load( "Shaders/Vertex.glsl", "Shaders/Fragment.glsl" );
    Camera camera;
    Loader loader;
    Height_Generator heightGen;

    GLuint texture = loader.loadTexture( "mc" ); //This is the texture atlas used by all blocks

    int size = 16;
    sf::Clock timer;
    std::vector<std::unique_ptr<Chunk>> m_chunks;

    Chunk_Positions positions;
    positions = positions.get( camera, size );

    for ( int x = positions.mxStart ; x < positions.mxEnd  ; x++ )
    {
        for ( int z = positions.mZStart ; z < positions.mZEnd ; z++)
        {
            m_chunks.emplace_back ( std::make_unique<Chunk>( loader, x, z, heightGen ) );
        }
    }


    size_t blocks = m_chunks.size() * Chunk::WIDTH * Chunk::HEIGHT * Chunk::WIDTH;
    std::cout << "Time for chunk creation: "    << timer.getElapsedTime().asSeconds() << ". Total Chunks: " << m_chunks.size() << std::endl;
    std::cout << "Total \"Blocks\": "           << blocks << std::endl;

    FPS fps;

    Matrix4 pers = glm::perspective( glm::radians( 90.0f ), w/ h, 0.01f, 1000.0f);
    glUseProgram ( shader );
    GLuint projectionLocation   = glGetUniformLocation ( shader, "projectionMatrix" );
    GLuint viewLocation         = glGetUniformLocation ( shader, "viewMatrix"       );
    GLuint modelLocation        = glGetUniformLocation ( shader, "modelMatrix"      );

    glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( pers ) );

    int camHeight = 50;

    camera.movePosition( {  0,
                            camHeight,
                            0 } );

    Vector2 currentPos = getChunkPos( camera );

    while ( window.isOpen() )
    {
        if ( currentPos != getChunkPos( camera ) ) {
            std::cout << "Chunk change" << std::endl;
            currentPos = getChunkPos( camera );
        }

        clearWindow();

        glUniformMatrix4fv ( viewLocation, 1, GL_FALSE, glm::value_ptr( createViewMatrix( camera ) ) );

        glActiveTexture ( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );

        camera.move();

        for ( auto& chunk : m_chunks )
        {
            glBindVertexArray ( chunk->tempMesh->getVAO() );
            glUniformMatrix4fv ( modelLocation, 1, GL_FALSE, glm::value_ptr( createTransforrmationMatrix
                                 ( chunk->tempMesh->pos,
                                   chunk->tempMesh->rot,
                                   chunk->tempMesh->sca ) ) );
            glDrawArrays( GL_TRIANGLES, 0, chunk->tempMesh->getVertexCount() );
        }

        window.display  ();
        checkForClose   ( window );
        fps.update();
    }


    return 0;
}


void checkForClose ( sf::RenderWindow& window )
{
    sf::Event e;
    while ( window.pollEvent( e ) )
    {
        if ( e.type == sf::Event::Closed )
        {
            window.close();
        }
        if ( e.type == sf::Event::KeyPressed )
        {
            if ( e.key.code == sf::Keyboard::Escape )
            {
                window.close();
            }
        }
    }
}

void clearWindow()
{
    glClear     ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 0.52, 0.81, 0.92, 1 );
}


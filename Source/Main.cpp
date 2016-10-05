#include <SFML/Graphics.hpp>

#include "OpenGL/GLEW/glew.h"
#include "OpenGL/GLM/glm_transformations.h"

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <thread>

#include "Camera.h"
#include "Utilities/Loader.h"
#include "Blocks/Blocks.h"

#include "shader_loader.h"

#include "Chunk/Chunk.h"

#include "Utilities/FPS.h"
#include "Window.h"
#include "Random.h"

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
/*
void handleChunks ( std::vector<Chunk*>& chunks, int size, Loader& loader )
{
    while ( true ) {
        for ( auto& chunk : chunks)
        {
            chunk->reset( loader );
        }
        std::cout << chunks.size() << std::endl;
    }
}
*/
int main()
{
    srand ( time ( NULL ) );

    double amplitude = Random::integer( 100, 150);
    double roughness = Random::decimal( 0.1, 0.3, 3);
    double octaves   = Random::integer( 3, 6);
    int seed = Random::integer(0, 32000) * Random::integer(0, 32000);

    int size    = Random::integer( 15, 30);
    int fog     = Random::integer( 0, 0);

    std::cout << "Do you want custom options? 0 for no, 1 for yes \n";
    int options;
    std::cin >> options;

    if ( options ) {

        std::cout   << "Please type in your, \n"
                    << "Amplitude (Height of Terrain), (Rec: 50-150) \n"
                    << "Rougness, (Rec: 0.01 to 1.0)\n"
                    << "Octaves (Higher = smoother, Rec: 2-5), \n"
                    << "And how big you want terrain: (Rec: 10-30) \n"
                    << "Fog, 0 = no, 1 = yes \n"
                    << "Seed \n";

        std::cin >> amplitude;
        std::cin >> roughness;
        std::cin >> octaves;
        std::cin >> size;
        std::cin >> fog;
        std::cin >> seed;
    }

    std::cout << "Amplitude: " << amplitude << std::endl;
    std::cout << "Roughness: " << roughness << std::endl;
    std::cout << "Octaves:   " << octaves   << std::endl;
    std::cout << "Size:      " << size      << std::endl;
    std::cout << "Fog:       " << fog  << std::endl;
    std::cout << "Seed:      " << seed << std::endl << std::endl;



    Height_Generator::setUp( amplitude, roughness, octaves, seed );
    Window::create();

    GLuint shader = GL::Shader::load( "Shaders/Vertex.glsl", "Shaders/Fragment.glsl" );
    Camera camera;
    Loader loader;

    GLuint texture = loader.loadTexture( "mc" ); //This is the texture atlas used by all blocks

    sf::Clock timer;
    std::vector<Chunk*> m_chunks;
    std::vector<Vector2> chunkPositions;

    Chunk_Positions positions;
    positions = positions.get( camera, size );

    for ( int x = positions.mxStart ; x < positions.mxEnd  ; x++ )
    {
        for ( int z = positions.mZStart ; z < positions.mZEnd ; z++)
        {
            m_chunks.emplace_back ( new Chunk( loader, x, z ) );
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
    GLuint fogLocation          = glGetUniformLocation ( shader, "fog"      );

    glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( pers ) );
    glUniform1i         ( fogLocation, fog );

    camera.movePosition( {  -10,
                            Chunk::highestBlock,
                            10 } );

    Vector2 currentPos = getChunkPos( camera );

    sf::Clock c;
    timer.restart();

    int totalVerticies = 0;
    for ( auto& chunk : m_chunks )
    {
        totalVerticies += chunk->tempMesh->getVertexCount();
    }

    std::cout << "Vertices: " << totalVerticies << std::endl;

    while ( Window::isOpen() )
    {
        int chunkZ = camera.getPosition().z / Chunk::WIDTH;
        int chunkX = camera.getPosition().x / Chunk::WIDTH;

        if ( currentPos != getChunkPos( camera ) ) {
            currentPos = getChunkPos( camera );
            std::cout << "On new chunk at location: " << chunkX << " " << chunkZ << std::endl;
        }




        float dt = c.restart().asSeconds();

        Window::clear();

        glUniformMatrix4fv ( viewLocation, 1, GL_FALSE, glm::value_ptr( createViewMatrix( camera ) ) );

        glActiveTexture ( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );

        camera.move( dt );

        for ( size_t i = 0 ; i < m_chunks.size() ; i++ )
        {
            auto& chunk = m_chunks.at( i );

            chunk->update();
            if ( chunk->isDelete() ) {
                m_chunks.erase( m_chunks.begin() + i );
            }
        }



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

        Window::update();
    }


    return 0;
}

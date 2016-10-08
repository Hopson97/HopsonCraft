#include "World.h"

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"

#include <iostream>

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

World::World()
    :   m_blockAtlas    ( 2048, 128 )
    ,   testShader      ( loadShader( "Shaders/Vertex.glsl", "Shaders/Fragment.glsl" ) )
    ,   matrix ( glm::perspective( glm::radians( 75.0f ), (float)Window::WIDTH/ (float)Window::HEIGHT, 0.01f, 1000.0f ) )
{
    m_blockAtlas.loadFromFile( "Blocks" );

    int size = 32;
    for ( int x = 0 ; x < size ; x++ )
    {
        for ( int z = 0 ; z < size ; z++ )
        {
            addChunk( { x, z } );
        }
    }
    assert( m_chunks.size() == size*size );
    camera.movePosition( { 0, 130, 10 } );
    assert( m_chunks.find( { 0, 0 } ) != m_chunks.end() );

    for ( auto& chunk : m_chunks )
    {
        chunk.second->generateMesh();
    }

    //TEMP
    glUseProgram ( testShader );

    projectionLocation   = glGetUniformLocation ( testShader, "projectionMatrix" );
    viewLocation         = glGetUniformLocation ( testShader, "viewMatrix"       );
    modelLocation        = glGetUniformLocation ( testShader, "modelMatrix"      );

    glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( matrix ) );

    glBindTexture( GL_TEXTURE_2D, m_blockAtlas.getId() );
    glActiveTexture ( GL_TEXTURE0 );
}
sf::Clock tempC;

void World :: draw ()
{
    float dt = tempC.restart().asSeconds();
    camera.move( dt );
    glUniformMatrix4fv ( viewLocation, 1, GL_FALSE, glm::value_ptr( createViewMatrix( camera ) ) );
    int drawCalls = 0;
    for ( auto& chunk : m_chunks )
    {
        Chunk& c = *chunk.second;

        glBindVertexArray ( c.getModel().getVAO() );
        glUniformMatrix4fv ( modelLocation, 1, GL_FALSE, glm::value_ptr( createTransforrmationMatrix
                                                                       (   c.position,
                                                                           c.rotation,
                                                                           c.scale     ) ) );


        glDrawArrays( GL_TRIANGLES, 0, c.getModel().getVertexCount() );
    }
}




void World :: addChunk ( const Vector2i& location )
{
    m_chunks[ location ] = std::make_unique<Chunk> ( &m_chunks, location, m_blockAtlas );
}

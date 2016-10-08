#include "World.h"

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"
#include "Application.h"

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

Vector2i pos ( 0, 0 );

World::World()
:   m_blockAtlas    ( 512, 16 )
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
    camera.movePosition( { 0, Chunk::maxHeight, 10 } );

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

    activeLocation       = glGetUniformLocation ( testShader, "isActive" );

    glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( matrix ) );

    glBindTexture( GL_TEXTURE_2D, m_blockAtlas.getId() );
    glActiveTexture ( GL_TEXTURE0 );

    std::cout << "Min Height: " << Chunk::minHeight << std::endl;
    std::cout << "Max Height: " << Chunk::maxHeight << std::endl;
    std::cout << "Blocks: " << m_chunks.size() * Chunk::WIDTH * Chunk::WIDTH * Chunk::HEIGHT << std::endl;

    pos.x = (int)camera.getPosition().x / Chunk::WIDTH;
    pos.z = (int)camera.getPosition().z / Chunk::WIDTH;
}

void World :: update ( float dt )
{
    Vector2i newPos = {
                        (int)camera.getPosition().x / Chunk::WIDTH,
                        (int)camera.getPosition().z / Chunk::WIDTH
                    };

    if ( newPos != pos ) {
        std::cout << "Moved to " << newPos.x << " " << newPos.z << std::endl;
        pos = newPos;
    }
    camera.move( dt );
}

void World :: draw ()
{
    glUniformMatrix4fv ( viewLocation, 1, GL_FALSE, glm::value_ptr( createViewMatrix( camera ) ) );

    for ( auto& chunk : m_chunks )
    {
        Chunk& c = *chunk.second;

        assert ( c.hasVertexData() );

        if ( c.m_location == pos )
        {
            glUniform1i ( activeLocation, 1 );
        }
        else
        {
            glUniform1i ( activeLocation, 0 );
        }

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
    assert( m_chunks.count( location ) == 0);
    m_chunks[ location ] = std::make_unique<Chunk> ( &m_chunks, location, m_blockAtlas );
}

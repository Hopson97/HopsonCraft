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
,   testChunk       ( 0, -5, m_blockAtlas )
,   testShader      ( loadShader( "Shaders/Vertex.glsl", "Shaders/Fragment.glsl" ) )
,   matrix          ( glm::perspective( glm::radians( 75.0f ), (float)Window::WIDTH/ (float)Window::HEIGHT, 0.01f, 1000.0f ) )
{
    testChunk.generateMesh();

    glUseProgram ( testShader );

    projectionLocation   = glGetUniformLocation ( testShader, "projectionMatrix" );
    viewLocation         = glGetUniformLocation ( testShader, "viewMatrix"       );
    modelLocation        = glGetUniformLocation ( testShader, "modelMatrix"      );

    glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( matrix ) );

    t.loadFromFile( "Blocks" );
    glBindTexture( GL_TEXTURE_2D, t.getId() );
    glActiveTexture ( GL_TEXTURE0 );

}
sf::Clock temp;

void World :: draw ()
{

    float dt = temp.restart().asSeconds();
    camera.move( dt );
    glUniformMatrix4fv ( viewLocation, 1, GL_FALSE, glm::value_ptr( createViewMatrix( camera ) ) );

    glBindVertexArray ( testChunk.getModel().getVAO() );

    glUniformMatrix4fv ( modelLocation, 1, GL_FALSE, glm::value_ptr( createTransforrmationMatrix
                                                    (   testChunk.position,
                                                        testChunk.rotation,
                                                        testChunk.scale     ) ) );


    glDrawArrays( GL_TRIANGLES, 0, testChunk.getModel().getVertexCount() );
}




void World :: addChunk ( const Vector2i& location )
{
    //m_chunks[ location ] = std::make_unique<Chunk>( m_chunks, location, m_blockAtlas );
}

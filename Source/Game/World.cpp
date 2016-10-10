#include "World.h"

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"
#include "Application.h"
#include "Height_Generator.h"
#include "Random.h"

#include <iostream>


World::World()
:   m_blockAtlas    ( 512, 16 )
,   m_player        ( m_chunks )
{
    //Height_Generator::setUp( 210, 0.5, 4, -1 );   //Hilly/ River Forest
    Height_Generator::setUp( 220, 0.4, 4, -1 );   //Very watery
    //Height_Generator::setUp( 250, 0.4, 5, -1 );   //Lakey hill forest
    //Height_Generator::setUp( 150, 0.6, 4, -1 );   //Very Very watery
    //Height_Generator::setUp( 250, 0.3, 5, -1 );   //Continental Ocean
    //Height_Generator::setUp( 125, 0.4, 5, -1 );   //Ocean
    //Height_Generator::setUp( 207, 0.503, 3, -1 );   //Hilly Swamp
    //Height_Generator::setUp( 222, 0.5, 5, -1 );   //Forest
    //Height_Generator::setUp( 229, 0.608, 4, -1 );   //Just forest
/*
    double amplitude = Random::integer( 170, 250);
    double roughness = Random::decimalD( 0.25, 0.8, 3);
    double octaves   = Random::integer( 3, 6);
    int seed = Random::integer(0, 32000) * Random::integer(0, 32000);

    Height_Generator::setUp( amplitude, roughness, octaves, seed );

    std::cout << "Amplitude: " << amplitude << std::endl;
    std::cout << "Roughness: " << roughness << std::endl;
    std::cout << "Octaves:   " << octaves   << std::endl;
    std::cout << "Seed:      " << seed << std::endl << std::endl;
/**/

    m_blockAtlas.loadFromFile( "Blocks_Sonic" );
    sf::Clock clock;
    int size = 50;
    for ( int x = 0 ; x < size ; x++ )
    {
        for ( int z = 0 ; z < size ; z++ )
        {
            addChunk( { x, z } );
        }
    }
    std::cout << "Chunk block data created, Time: " << clock.getElapsedTime().asSeconds() << std::endl;
    for ( auto& chunk : m_chunks )
    {
        chunk.second->generateMesh();
    }
    std::cout << "Chunk vertex data created, Time: " << clock.getElapsedTime().asSeconds() << std::endl;
}

void World :: update ( float dt )
{
    m_player.update( dt );
}

void World :: draw ()
{
    for ( auto& chunk : m_chunks )
    {
        m_chunkRenderer.renderChunk( *chunk.second );
    }
    m_chunkRenderer.render( m_player.getCamera() );
}




void World :: addChunk ( const Vector2i& location )
{
    m_chunks[ location ] = std::make_unique<Chunk> ( &m_chunks, location, m_blockAtlas );
}

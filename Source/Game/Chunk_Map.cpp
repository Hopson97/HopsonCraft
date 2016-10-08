#include "Chunk_Map.h"



Chunk_Map :: Chunk_Map()
:   m_blockAtlas    ( 2048, 128 )
{
    m_blockAtlas.loadFromFile( "Blocks" );
}

void Chunk_Map :: draw ( int ml)
{

}

Chunk& Chunk_Map::get(int x, int z)
{
    return *m_chunks.at( x * m_size + z );
}

#include "Chunk_Map.h"

Chunk_Map::Chunk_Map()
{
    //ctor
}

Chunk* Chunk_Map::getChunkAt (const Chunk_Position& location)
{
    if (m_chunks.find(location) != m_chunks.end()) {
        return &*m_chunks.at(location);
    } else {
        return nullptr;
    }
}



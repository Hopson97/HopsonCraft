#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <unordered_map>
#include <memory>

#include "Chunk_Position.h"
#include "Chunk.h"

class Chunk_Map
{
    public:
        Chunk_Map();
        Chunk* getChunkAt (const Chunk_Position& location);

    private:
        std::unordered_map<Chunk_Position, std::unique_ptr<Chunk>> m_chunks;
};

#endif // CHUNK_MAP_H

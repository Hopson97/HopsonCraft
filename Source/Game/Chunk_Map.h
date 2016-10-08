#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <vector>

#include "Chunk.h"
#include "Texture_Atlas.h"

class Chunk_Map
{
    public:
        Chunk_Map();

        Chunk& get ( int x, int z );

        void draw ( int ml );

    private:
        std::vector<Chunk_Ptr> m_chunks;
        Texture_Atlas m_blockAtlas;
        int m_size = 8;
};

#endif // CHUNK_MAP_H

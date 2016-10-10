#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "Chunk/Chunk.h"
#include "Vector.h"
#include "Texture_Atlas.h"

#include "Player.h"
#include "Chunk_Renderer.h"


class World
{
    public:
        World();

        void update ( float dt );
        void draw   ();

        static int worldSize;

    private:
        void addChunk ( const Vector2i& location );


    private:
        std::unordered_map<Vector2i, Chunk_Ptr> m_chunks;
        Texture_Atlas m_blockAtlas;;

        Chunk_Renderer m_chunkRenderer;

        Player  m_player;
};

#endif // WORLD_H

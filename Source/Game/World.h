#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "Chunk/Chunk.h"
#include "Vector.h"
#include "Texture_Atlas.h"

#include "Player.h"
#include "Master_Renderer.h"


class World
{
    public:
        World   ();

        void update ( float dt );
        void draw   ();

        static int worldSize;

    private:
        void updateChunks   ();

        void addChunk       ( const Vector2i& location );

        void generateChunks ();


    private:
        std::unordered_map<Vector2i, Chunk_Ptr> m_chunks;
        std::vector<Chunk*> m_updateChunks;
        Texture_Atlas m_blockAtlas;;

        Master_Renderer m_renderer;

        Player  m_player;
};

#endif // WORLD_H

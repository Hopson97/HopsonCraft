#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "Chunk/Chunk.h"
#include "Vector.h"
#include "Texture_Atlas.h"

#include "Player.h"
#include "Master_Renderer.h"

struct RenderArea;

class World
{
    public:
        World   ();
        ~World  ();

        void update ( float dt );
        void draw   ();

    private:
        void updateChunks   ();

        void addChunk       ( const Vector2i& location );

        void manageChunks   ();
        void generateChunks ( const RenderArea& area );
        void checkChunks    ( const RenderArea& area );


    private:
        std::unordered_map<Vector2i, Chunk_Ptr> m_chunks;
        std::vector<Chunk*> m_updateChunks;
        Texture_Atlas m_blockAtlas;;

        Master_Renderer m_renderer;

        Player  m_player;
        Vector2i lastPlayerPos;


        bool m_isRunning = true;

        int m_renderDistance    = 16;
        int m_loadDistance      = 2;
};

#endif // WORLD_H

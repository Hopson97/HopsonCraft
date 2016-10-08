#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "Chunk.h"
#include "Vector.h"
#include "Texture_Atlas.h"

#include "Camera.h"
#include "Chunk_Map.h"
#include "Chunk_Renderer.h"

class World
{
    public:
        World();

        void update ( float dt );
        void draw   ();

    private:
        void addChunk ( const Vector2i& location );


    private:
        std::unordered_map<Vector2i, Chunk_Ptr> m_chunks;
        Texture_Atlas m_blockAtlas;;

        Chunk_Renderer m_chunkRenderer;

        Camera  m_camera;
};

#endif // WORLD_H

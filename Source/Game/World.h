#ifndef WORLD_H
#define WORLD_H

#include "OpenGL/Glm/glm_transformations.h"

#include "Chunk.h"
#include "Vector.h"
#include "Texture_Atlas.h"
#include "Texture.h"

#include "Camera.h"

class World
{
    public:
        World();

        void draw ();

    private:
        void addChunk ( const Vector2i& location );


    private:
        std::map<Vector2i, Chunk_Ptr> m_chunks;

        bool m_isRunning;

        Texture_Atlas m_blockAtlas;

        Camera  camera;
        Chunk   testChunk;
        GLuint  testShader;
        Matrix4 matrix;
        Texture t;

        GLuint projectionLocation;
        GLuint viewLocation;
        GLuint modelLocation;
};

#endif // WORLD_H

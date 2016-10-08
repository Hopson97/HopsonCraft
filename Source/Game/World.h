#ifndef WORLD_H
#define WORLD_H

#include "OpenGL/Glm/glm_transformations.h"

#include "Chunk.h"
#include "Vector.h"
#include "Texture_Atlas.h"
#include "Texture.h"

#include "Camera.h"

#include <unordered_map>

class World
{
    public:
        World();

        void draw ();

    private:
        void addChunk ( const Vector2i& location );


    private:
        std::unordered_map<Vector2i, Chunk_Ptr> m_chunks;

        Texture_Atlas m_blockAtlas;

        bool m_isRunning = true;

        //temp
        Camera  camera;
        GLuint  testShader;
        Matrix4 matrix;

        GLuint projectionLocation;
        GLuint viewLocation;
        GLuint modelLocation;
};

#endif // WORLD_H

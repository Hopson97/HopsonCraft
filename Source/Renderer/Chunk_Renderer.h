#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <vector>
#include <memory>
#include "Chunk_Shader.h"

#include "../World/Chunk/Chunk.h"
#include "../Player/Camera.h"
#include "../Maths/Matrix_Maths.h"
#include "../D_Settings.h"

class Chunk;
class Camera;

template<class T>
class Chunk_Renderer
{
    public:
        void addChunk (const Chunk& chunk)
        {
                m_chunks.push_back(&chunk);
        }

        void render (const Camera& camera)
        {
            m_shader.useProgram();
            m_shader.loadCameraMatrix(camera);
            m_shader.loadSkyColour  ({Settings::SKY_RED,
                                      Settings::SKY_GREEN,
                                      Settings::SKY_BLUE
                                    });
            prepareRender();

            for (const Chunk* chunk : m_chunks)
            {
                prepareChunk(*chunk);
                drawChunk   (*chunk);
            }

            m_chunks.clear();
            glBindVertexArray ( 0 );
            glUseProgram(0);
        }

    protected:
        const T& getShader() const
        {
            return m_shader;
        }

        virtual void prepareRender  () = 0;
        virtual void prepareChunk   (const Chunk& chunk) = 0;
        virtual void drawChunk      (const Chunk& chunk) = 0;

    private:
        T m_shader;
        std::vector<const Chunk*> m_chunks;
};

#endif // CHUNK_RENDERER_H

#include "Chunk_Renderer.h"

#include "../World/Chunk/Chunk.h"
#include "../Player/Camera.h"
#include "../Maths/Matrix_Maths.h"
#include "../D_Settings.h"

#include <iostream>
/*
Chunk_Renderer::Chunk_Renderer(std::unique_ptr<Shader::Chunk_Shader> shader)
:   m_shader (std::move(shader))
{ }

void Chunk_Renderer::addChunk (const Chunk& chunk)
{
    m_chunks.push_back(&chunk);
}

void Chunk_Renderer::render (const Camera& camera)
{
    m_shader->useProgram();
    m_shader->loadCameraMatrix(camera);
    m_shader->loadSkyColour  ({Settings::SKY_RED,
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

Shader::Chunk_Shader& Chunk_Renderer::getShader()
{
    return *m_shader;
}

*/

#ifndef FLORA_RENDERER_H
#define FLORA_RENDERER_H

#include <SFML/System/Clock.hpp>

#include "../Shaders/Flora_Shader.h"

#include "Chunk_Renderer.h"

class Chunk;

class Flora_Renderer : public Chunk_Renderer<Shader::Flora_Shader>
{
    public:
        Flora_Renderer();

    private:
        void prepareRender  () override;
        void prepareChunk   (const Chunk& chunk) override;
        void drawChunk      (const Chunk& chunk) override;

        sf::Clock m_timer;
};

#endif // FLORA_RENDERER_H

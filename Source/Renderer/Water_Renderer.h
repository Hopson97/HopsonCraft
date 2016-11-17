#ifndef WATER_RENDERER_H
#define WATER_RENDERER_H

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Water_Shader.h"

#include "Chunk_Renderer.h"

class Chunk;


class Water_Renderer : public Chunk_Renderer<Shader::Water_Shader>
{
    public:
        Water_Renderer();

    private:
        void prepareRender  () override;
        void prepareChunk   (const Chunk& chunk) override;
        void drawChunk      (const Chunk& chunk) override;

        sf::Clock m_timer;
};

#endif // WATER_RENDERER_H

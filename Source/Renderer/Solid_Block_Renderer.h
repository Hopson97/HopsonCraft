#ifndef SOLID_GROUND_RENDERER_H
#define SOLID_GROUND_RENDERER_H

#include "Chunk_Renderer.h"

#include "../Shaders/Solid_Block_Shader.h"

class Chunk;

class Solid_Block_Renderer : public Chunk_Renderer<Shader::Solid_Block_Shader>
{
    public:
        Solid_Block_Renderer();

    private:
        void prepareRender  () override;
        void prepareChunk   (const Chunk& chunk) override;
        void drawChunk      (const Chunk& chunk) override;
};

#endif // SOLID_GROUND_RENDERER_H

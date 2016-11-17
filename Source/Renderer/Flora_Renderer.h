#ifndef FLORA_RENDERER_H
#define FLORA_RENDERER_H

#include "Chunk_Renderer.h"
#include "Flora_Shader.h"

class Chunk;

class Flora_Renderer : public Chunk_Renderer<Shader::Flora_Shader>
{
    public:
        Flora_Renderer();

    private:
        void prepareRender  () override;
        void prepareChunk   (const Chunk& chunk) override;
        void drawChunk      (const Chunk& chunk) override;
};

#endif // FLORA_RENDERER_H

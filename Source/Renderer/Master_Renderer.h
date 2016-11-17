#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include "Solid_Block_Renderer.h"
#include "Water_Renderer.h"
#include "Flora_Renderer.h"
#include "SFML_Renderer.h"
#include "Screen_Shader.h"
#include "Framebuffer_Object.h"
#include "Model/Model.h"

#include <memory>

class Chunk;
class Camera;

class Master_Renderer
{
    public:
        Master_Renderer();

        void prepare ();

        void processChunk       (const Chunk& chunk);
        void processSfDrawable  (const sf::Drawable& sfDrawable);

        void render (const Camera& camera);

    private:
        void drawScene(const Camera& camera);

        void drawToQuad();

        Solid_Block_Renderer m_chunkRenderer;
        Water_Renderer m_waterRenderer;
        Flora_Renderer m_floraRenderer;
        SFML_Renderer  m_sfmlRenderer;

        Framebuffer_Object m_framebuffer;

        Shader::Screen_Shader m_colourShader;

        Model m_quad;
};

#endif // MASTER_RENDERER_H

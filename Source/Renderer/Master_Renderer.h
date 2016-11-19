#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include "../Shaders/Screen_Shader.h"
#include "../PostFX/Framebuffer_Object.h"
#include "../Model/Model.h"

#include "Solid_Block_Renderer.h"
#include "Water_Renderer.h"
#include "Flora_Renderer.h"
#include "SFML_Renderer.h"

#include <memory>

class Chunk;
class Camera;

class Master_Renderer
{
    public:
        Master_Renderer();

        void clear ();

        void draw (const Chunk& chunk);
        void draw (const sf::Drawable& sfDrawable);

        void update (const Camera& camera);

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

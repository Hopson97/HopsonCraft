#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <memory>

#include "../Shaders/Screen_Shader.h"
#include "../PostFX/Framebuffer_Object.h"
#include "../Model/Model.h"

#include "Solid_Block_Renderer.h"
#include "Water_Renderer.h"
#include "Flora_Renderer.h"
#include "SFML_Renderer.h"
#include "Skybox_Renderer.h"

class Chunk;
class Entity;

enum class Post_FX
{
    Blue,
    Blur
};

class Master_Renderer
{
    public:
        Master_Renderer();

        void clear ();

        void draw (const Chunk& chunk);
        void draw (const sf::Drawable& sfDrawable);

        void update (const Camera& camera);

        void addPostFX(Post_FX postFx);

    private:
        void drawScene(const Camera& camera);

        void drawToQuad();

        std::vector<Shader::Screen_Shader*> m_postFXPasses;

        Solid_Block_Renderer    m_chunkRenderer;
        Water_Renderer          m_waterRenderer;
        Flora_Renderer          m_floraRenderer;
        SFML_Renderer           m_sfmlRenderer;
        Skybox_Renderer         m_skyboxRenderer;

        Framebuffer_Object m_framebuffer;

        Shader::Screen_Shader m_simpleShader;
        Shader::Screen_Shader m_blueShader;
        Shader::Screen_Shader m_blurShader;

        Model m_quad;
};

#endif // MASTER_RENDERER_H

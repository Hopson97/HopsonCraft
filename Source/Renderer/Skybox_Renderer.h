#ifndef SKYBOX_RENDERER_H_INCLUDED
#define SKYBOX_RENDERER_H_INCLUDED

#include "../Model/Model.h"
#include "../Shaders/Skybox_Shader.h"
#include "../Texture/Texture.h"

class Camera;

class Skybox_Renderer
{
    public:
        Skybox_Renderer();

        void render(const Camera& camera);

    private:
        Model                   m_model;
        Texture                 m_texture;
        Shader::Skybox_Shader   m_shader;
};

#endif // SKYBOX_RENDERER_H_INCLUDED

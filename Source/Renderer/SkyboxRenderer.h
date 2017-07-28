#ifndef RSKYBOX_H_INCLUDED
#define RSKYBOX_H_INCLUDED

#include "../Shaders/SimpleShader.h"
#include "../Model.h"

namespace Texture
{
    class CubeTexture;
}

class Camera;

namespace Renderer
{
    class SkyBox
    {
        public:
            SkyBox();

            void draw(const Texture::CubeTexture& cubeTex);

            void update(const Camera& camera);

        private:
             SimpleShader m_shader;

             Model m_cube;

            const Texture::CubeTexture* m_pCubeMap = nullptr;
    };
}

#endif // RSKYBOX_H_INCLUDED

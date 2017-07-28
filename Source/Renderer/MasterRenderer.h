#ifndef MASTER_RENDER_H_INCLUDED
#define MASTER_RENDER_H_INCLUDED

#include "SFMLRenderer.h"
#include "SimpleRenderer.h"
#include "SkyboxRenderer.h"

struct Camera;


class MasterRenderer
{
    public:
        void clear();

        void update(const Camera& camera);

        void draw(const Vector3& location);
        void draw(const sf::Drawable& drawable);
        void draw(const Cube& cube);

        void draw(const Texture::CubeTexture& tex);

    private:
        SFMLRenderer       m_sfmlRenderer;
        SimpleRenderer     m_simpleRenderer;
        Renderer::SkyBox      m_skyBoxRenderer;
};


#endif // MASTER_RENDER_H_INCLUDED

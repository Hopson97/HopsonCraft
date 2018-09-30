#ifndef MASTER_RENDER_H_INCLUDED
#define MASTER_RENDER_H_INCLUDED

#include "SFMLRenderer.h"
#include "SimpleRenderer.h"

struct Camera;

class MasterRenderer
{
    public:
        void update(const Camera& camera);

        void draw(const Vector3& location);
        void draw(const sf::Drawable& drawable);
        void draw(const Cube& cube);

    private:
        SFMLRenderer       m_sfmlRenderer;
        SimpleRenderer     m_simpleRenderer;
};

#endif // MASTER_RENDER_H_INCLUDED

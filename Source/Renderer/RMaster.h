#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "RSFML.h"
#include "RSimple.h"

struct Camera;

namespace Renderer
{
    class Master
    {
        public:
            void clear();

            void update(const Camera& camera);

            void draw(const Vector3& location);
            void draw(const sf::Drawable& drawable);
            void draw(const Cube& cube);

        private:
            RSFML       m_sfmlRenderer;
            RSimple     m_simpleRenderer;
    };
}

#endif // MASTER_H_INCLUDED

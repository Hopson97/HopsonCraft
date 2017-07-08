#ifndef RSFML_H_INCLUDED
#define RSFML_H_INCLUDED

#include <vector>

namespace sf
{
    class Drawable;
}

namespace Renderer
{
    class RSFML
    {
        public:
            void draw(const sf::Drawable& drawbale);

            void update();

        private:
            std::vector<const sf::Drawable*> m_drawables;
    };
}

#endif // RSFML_H_INCLUDED

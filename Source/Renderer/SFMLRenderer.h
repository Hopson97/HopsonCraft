#ifndef SFML_RENDER_H_INCLUDED
#define SFML_RENDER_H_INCLUDED

#include <vector>

namespace sf
{
    class Drawable;
}


class SFMLRenderer
{
    public:
        void draw(const sf::Drawable& drawbale);

        void update();

    private:
        std::vector<const sf::Drawable*> m_drawables;
};

#endif // SFML_RENDER_H_INCLUDED

#ifndef SFML_RENDERER_H
#define SFML_RENDERER_H

#include <SFML/Graphics.hpp>

#include <vector>

class SFML_Renderer
{
    public:
        void addSfDrawable(const sf::Drawable& sfDrawable);

        void render();

    private:
        std::vector<const sf::Drawable*> m_drawables;
};

#endif // SFML_RENDERER_H

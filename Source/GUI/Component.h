#ifndef COMPONENT_GUI_H
#define COMPONENT_GUI_H

#include <SFML/Graphics.hpp>

class Master_Renderer;

namespace GUI
{
    class Component
    {
        public:
            Component();

            virtual void input  (const sf::Event& e) = 0;
            virtual void update () = 0;
            virtual void draw   (Master_Renderer& renderer) = 0;

        protected:
            static sf::Texture guiTexture;
            static sf::Font    guiFont;
    };
}

#endif // COMPONENT_GUI_H

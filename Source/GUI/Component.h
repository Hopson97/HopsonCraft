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
            virtual ~Component(){}

            virtual void input  (const sf::Event& e) = 0;
            virtual void update () = 0;
            virtual void draw   (Master_Renderer& renderer) = 0;

            virtual void setPosition (const sf::Vector2f& position) = 0;

            virtual const sf::Vector2f getSize () const = 0;

        protected:
            bool touchingMouse (const sf::Shape& sprite) const;

            static sf::Texture guiTexture;
            static sf::Font    guiFont;
    };

    class Empty_Component : public Component
    {
        public:
            void input  (const sf::Event& e){}
            void update (){}
            void draw   (Master_Renderer& renderer){}

            void setPosition (const sf::Vector2f& position){}

            const sf::Vector2f getSize () const { return {0,0}; }
    };
}

#endif // COMPONENT_GUI_H

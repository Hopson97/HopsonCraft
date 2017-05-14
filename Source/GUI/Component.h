#ifndef COMPONENT_GUI_H
#define COMPONENT_GUI_H

#include <SFML/Graphics.hpp>

namespace Renderer { class Master; }

namespace GUI
{
    class Component
    {
        public:
            static constexpr int BASE_WIDTH     = 500;
            static constexpr int BASE_HEIGHT    = 100;

            Component();
            virtual ~Component(){}

            virtual void input  (const sf::Event& e) = 0;
            virtual void update () = 0;
            virtual void draw   (Renderer::Master& renderer) = 0;

            virtual void setPosition (const sf::Vector2f& position) = 0;

            virtual const sf::Vector2f getSize () const = 0;

        protected:
            bool touchingMouse  (const sf::Shape& sprite) const;
            bool clicked        (const sf::Shape& sprite, const sf::Event& e) const;
            void initText       (sf::Text& text, int size, const std::string& title);
            sf::Text initText   (int size, const std::string& title);

            static sf::Texture guiTexture;
    };

    class Empty_Component : public Component
    {
        public:
            void input  (const sf::Event& e){}
            void update (){}
            void draw   (Renderer::Master& renderer){}

            void setPosition (const sf::Vector2f& position){}

            const sf::Vector2f getSize () const { return {0,0}; }
    };
}

#endif // COMPONENT_GUI_H

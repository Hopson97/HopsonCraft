#ifndef MENU_H
#define MENU_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Component.h"

class Master_Renderer;

namespace GUI
{
    enum class Layout
    {
        Center
    };

    class Base_Menu
    {
        public:
            Base_Menu (Layout layout);

            void addComponent(std::unique_ptr<Component> component);

            void input  (const sf::Event& e);
            void update ();
            void draw   (Master_Renderer& renderer);

        private:
            void addComponentCenter(std::unique_ptr<Component>& component);

            std::vector<std::unique_ptr<Component>> m_components;

            Layout m_layout;
    };
}

#endif // MENU_H

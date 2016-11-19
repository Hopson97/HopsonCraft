#ifndef MENU_H
#define MENU_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Component.h"

class Master_Renderer;

namespace GUI
{
    class Base_Menu
    {
        public:
            void addComponent(std::unique_ptr<Component> component);

            void input  (const sf::Event& e);
            void update ();
            void draw   (Master_Renderer& renderer);

        private:
            std::vector<std::unique_ptr<Component>> m_components;
    };
}

#endif // MENU_H

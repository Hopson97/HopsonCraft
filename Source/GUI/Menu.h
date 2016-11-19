#ifndef MENU_H
#define MENU_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "Background.h"

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

            void addBackgroud(const std::string& name);
            void addComponent(std::unique_ptr<Component> component);

            void input  (const sf::Event& e);
            void update ();
            void draw   (Master_Renderer& renderer);

        private:
            void addComponentCenter(std::unique_ptr<Component>& component);

            std::vector<std::unique_ptr<Component>> m_components;
            std::unique_ptr<Background> m_background;

            Layout m_layout;

    };
}

#endif // MENU_H

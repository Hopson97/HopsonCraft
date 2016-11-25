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
        Center,
        Grid2x
    };

    class Base_Menu
    {
        public:
            Base_Menu (Layout layout);
            virtual ~Base_Menu() = default;

            void addBackgroud(const sf::Texture& texture);
            void addComponent(std::unique_ptr<Component> component);
            void addPadding  (int amount) { m_currentY += amount; }

            void input  (const sf::Event& e);
            void update ();
            void draw   (Master_Renderer& renderer);

            void clear  ();

        private:
            void addComponentCenter(std::unique_ptr<Component>& component);
            void addComponentGrid2x(std::unique_ptr<Component>& component);

            std::vector<std::unique_ptr<Component>> m_components;
            std::unique_ptr<Background> m_background;

            Layout m_layout;

            int m_currentX = 0;
            int m_currentY = 15;

    };
}

#endif // MENU_H

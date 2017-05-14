#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "Background.h"

namespace Renderer { class Master; }

namespace GUI
{
    enum class Layout
    {
        Center,
        Grid2x
    };

    class Panel
    {
        public:
            Panel (Layout layout);
            virtual ~Panel() = default;

            void addBackgroud(const sf::Texture& texture);
            void addComponent(std::unique_ptr<Component> component);
            void addPadding  (int amount) { m_currentY += amount; }

            void input  (const sf::Event& e);
            void update ();
            void draw   (Renderer::Master& renderer);

            void clear  ();

        private:
            void addComponentCenter(std::unique_ptr<Component>& component);
            void addComponentGrid2x(std::unique_ptr<Component>& component);

            std::vector<std::unique_ptr<Component>> m_components;
            std::unique_ptr<Background> m_background;

            Layout m_layout;

            int m_currentX = 0;
            int m_currentY = 15;

            bool m_isGrid2xleft = true;
            int  m_2xRow = 0;
            int  m_2xCount = 0;

    };
}

#endif // PANEL_H_INCLUDED

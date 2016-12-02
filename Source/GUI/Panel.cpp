#include "Panel.h"

#include "../Util/Display.h"

namespace GUI
{
    Panel::Panel(Layout layout)
    :   m_layout (layout)
    { }

    void Panel::addBackgroud(const sf::Texture& texture)
    {
        m_background = std::make_unique<Background>(texture);
    }


    void Panel::addComponent(std::unique_ptr<Component> component)
    {
        switch(m_layout)
        {
            case Layout::Center:
                addComponentCenter(component);
                break;

            case Layout::Grid2x:
                addComponentGrid2x(component);
                break;
        }

        m_components.push_back(std::move(component));
    }

    void Panel::input(const sf::Event& e)
    {
        for (auto& c : m_components)
        {
            c->input(e);
        }
    }

    void Panel::update()
    {
        for (auto& c : m_components)
        {
            c->update();
        }
    }

    void Panel::draw(Master_Renderer& renderer)
    {
        if(m_background)
            m_background->draw(renderer);

        for (auto& c : m_components)
        {
            c->draw(renderer);
        }
    }

    void Panel::addComponentCenter(std::unique_ptr<Component>& component)
    {
        component->setPosition({Display::get().getSize().x / 2 - component->getSize().x / 2,
                                float(m_currentY) });

        m_currentY += component->getSize().y + 10;
    }

    void Panel::addComponentGrid2x(std::unique_ptr<Component>& component)
    {

    }


    void Panel::clear()
    {
        m_components.clear();
        m_components.shrink_to_fit();
        m_currentX = 0;
        m_currentY = 0;
    }


}   //namespace GUI

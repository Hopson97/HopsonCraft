#include "Menu.h"

#include "../Util/Display.h"

namespace GUI
{
    Base_Menu::Base_Menu(Layout layout)
    :   m_layout (layout)
    { }

    void Base_Menu::addBackgroud(const sf::Texture& texture)
    {
        m_background = std::make_unique<Background>(texture);
    }


    void Base_Menu::addComponent(std::unique_ptr<Component> component)
    {
        switch(m_layout)
        {
            case Layout::Center:
                addComponentCenter(component);
                break;
        }

        m_components.push_back(std::move(component));
    }

    void Base_Menu::input(const sf::Event& e)
    {
        for (auto& c : m_components)
        {
            c->input(e);
        }
    }

    void Base_Menu::update()
    {
        for (auto& c : m_components)
        {
            c->update();
        }
    }

    void Base_Menu::draw(Master_Renderer& renderer)
    {
        if(m_background)
            m_background->draw(renderer);

        for (auto& c : m_components)
        {
            c->draw(renderer);
        }
    }

    void Base_Menu::addComponentCenter(std::unique_ptr<Component>& component)
    {
        component->setPosition({Display::get().getSize().x / 2 - component->getSize().x / 2,
                                float(m_currentY) });

        m_currentY += component->getSize().y + 10;
    }

}   //namespace GUI

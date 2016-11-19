#include "Menu.h"

#include "../Util/Display.h"

namespace GUI
{
    Base_Menu::Base_Menu(Layout layout)
    :   m_layout (layout)
    { }

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
        for (auto& c : m_components)
        {
            c->draw(renderer);
        }
    }

    void Base_Menu::addComponentCenter(std::unique_ptr<Component>& component)
    {
        component->setPosition({Display::WIDTH / 2,
                               100 + m_components.size() * component->getSize().y});
    }

}

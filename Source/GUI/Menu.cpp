#include "Menu.h"

namespace GUI
{
    void Base_Menu::addComponent(std::unique_ptr<Component> component)
    {
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
}

#include "Image.h"

#include "../Renderer/Master_Renderer.h"

namespace GUI
{
    Image::Image(const std::string& name, const sf::Vector2f& size)
    {
        m_texture.loadFromFile(name + ".png");

        m_quad.setSize(size);
        m_quad.setTexture(&m_texture);
    }

    void Image::input(const sf::Event& e)
    { }

    void Image::update()
    { }

    void Image::draw(Master_Renderer& renderer)
    {
        renderer.draw(m_quad);
    }

    void Image::setPosition(const sf::Vector2f& position)
    {
        m_quad.setPosition(position);
    }

    const sf::Vector2f Image::getSize() const
    {
        return m_quad.getSize();
    }
}

#include "RSFML.h"

#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "../Display.h"

namespace Renderer
{
    void RSFML::draw(const sf::Drawable& drawbale)
    {
        m_drawables.push_back(&drawbale);
    }

    void RSFML::update()
    {
        glDisable(GL_DEPTH_TEST);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);

        Display::get().pushGLStates();
        Display::get().resetGLStates();


        for (const auto& sfd : m_drawables)
        {
            Display::sfDraw(*sfd);
        }

        Display::get().popGLStates();
        glEnable(GL_DEPTH_TEST);

        m_drawables.clear();
    }
}

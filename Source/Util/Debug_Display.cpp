#include "Debug_Display.h"

#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "Display.h"

namespace Debug_Display
{
    namespace
    {
        std::unique_ptr<sf::Font> font;
        std::unique_ptr<sf::Text> generalText;
        std::unique_ptr<sf::Text> fpsText;
        std::string textString;
        sf::Clock updateTimer;
    }

    void init()
    {
        font = std::make_unique<sf::Font>();
        font->loadFromFile("Data/Font/rs.ttf");
        generalText = std::make_unique<sf::Text>("Test", *font, 20);
        fpsText     = std::make_unique<sf::Text>("Test", *font, 20);

        generalText->move(0, 50);
    }

    void addFPS(float fps)
    {
        fpsText->setString("FPS: " + std::to_string((int)fps));
    }

    void addText(const std::string& text)
    {
        textString.append(text + "\n");
    }

    void draw()
    {
        generalText->setString(textString);
        if (updateTimer.getElapsedTime().asSeconds() > 1.0f)
        {
            updateTimer.restart();
            textString.clear();
        }
        Display::sfDraw(*generalText);
        Display::sfDraw(*fpsText);
    }
}

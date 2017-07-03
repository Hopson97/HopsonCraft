#include "Debug.h"

#include "../ResourceManagers/ResourceHolder.h"
#include "../Renderer/RMaster.h"

Debug_HUD::Section::Section(std::string&& stringFormat, const sf::Vector2f& textPosition, const void* var)
:   format      (std::move(stringFormat))
,   position    (textPosition)
,   info        (var)
{
    text.setCharacterSize       (20);
    text.setFont                (getResources().fonts.get("rs"));
    //text.setOutlineThickness    (1);
    //text.setOutlineColor        (sf::Color::Black);
    text.setColor(sf::Color::White);
    text.setPosition(position);
}


void Debug_HUD::addDebugSector(std::string&& format,
                               const sf::Vector2f& position,
                               const void* info)
{
    m_debugSectors.emplace_back(std::move(format), position, info);
}

void Debug_HUD::draw(Renderer::Master& master) noexcept
{
    for (auto& sect : m_debugSectors)
    {
        drawSection(sect, master);
    }
}

void Debug_HUD::drawSection(Section& section, Renderer::Master& master) noexcept
{
    char buffer[256];

    std::snprintf(buffer,
                  sizeof(buffer),
                  section.format.c_str(),
                  *(float*)section.info);

    section.text.setString  (buffer);
    master.draw (section.text);
}



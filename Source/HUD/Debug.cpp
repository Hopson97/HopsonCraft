#include "Debug.h"

#include "../ResourceManagers/ResourceHolder.h"
#include "../Renderer/MasterRenderer.h"

Debug_HUD::Section::Section(std::string&& stringFormat, const sf::Vector2f& textPosition, const void* var)
:   format      (std::move(stringFormat))
,   position    (textPosition)
,   info        (var)
{
    text.setCharacterSize       (20);
    text.setFont                (ResourceHolder::getFont("rs"));
    text.setOutlineThickness    (1);
    text.setOutlineColor        (sf::Color::Black);
    text.setPosition(position);
}


void Debug_HUD::addDebugSector(std::string&& format,
                               const void* info)
{
    m_debugSectors.emplace_back(std::move(format), sf::Vector2f{5, y}, info);
    y += 27;
}

void Debug_HUD::draw(MasterRenderer& master)
{
    for (auto& sect : m_debugSectors)
    {
        drawSection(sect, master);
    }
}

void Debug_HUD::drawSection(Section& section, MasterRenderer& master)
{
    char buffer[256];

    std::snprintf(buffer,
                  sizeof(buffer),
                  section.format.c_str(),
                  *(float*)section.info);

    section.text.setString  (buffer);
    master.draw (section.text);
}



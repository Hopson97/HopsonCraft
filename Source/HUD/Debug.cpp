#include "Debug.h"

#include "../Resource_Managers/Resource_Holder.h"
#include "../Renderer/RMaster.h"

Debug_HUD::Section::Section(std::string&& format, const sf::Vector2f& position, const void* info)
:   format      (std::move(format))
,   position    (position)
,   info        (info)
{
    text.setCharacterSize       (15);
    text.setFont                (getResources().getFont(Font_ID::RS));
    text.setOutlineThickness    (1);
    text.setOutlineColor        (sf::Color::Black);
    text.setPosition(position);
}


void Debug_HUD::addDebugSector(std::string&& format,
                               const sf::Vector2f& position,
                               const void* info)
{
    m_debugSectors.emplace_back(std::move(format), position, info);
}

void Debug_HUD::draw(Renderer::Master& master)
{
    for (auto& sect : m_debugSectors)
    {
        drawSection(sect, master);
    }
}

void Debug_HUD::drawSection(Section& section, Renderer::Master& master)
{
    char buffer[256];

    std::snprintf(buffer,
                  sizeof(buffer),
                  section.format.c_str(),
                  *(float*)section.info);

    section.text.setString  (buffer);
    master.draw (section.text);
}



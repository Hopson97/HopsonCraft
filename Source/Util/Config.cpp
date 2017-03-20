#include "Config.h"
#include <sstream>
#include <string>

Config::Config() {
    setDefaultVideoMode();
    setDefaultKeybindings();
}

void Config::loadFromStream(std::string const& filename, std::istream& is)
{
    ConfigParser parser;
    parser.parse(filename, is);
    while (!parser.atEnd())
    {
        if (parser.atKVP())
        {
            parser.error("KVP without section");
        }

        auto header = parser.getHeader();

        if (header == "screen")
        {
            loadScreenSettingsFromStream(parser);
        }
        else if (header == "keyboard")
        {
            loadKeybindingsFromStream(parser);
        }
        else
        {
            parser.error("Unrecognised section " + header);
        }
    }
}

sf::Keyboard::Key Config::getKey(Key_Binds::Control control) const
{
    return m_keybindings.at(control);
}

sf::VideoMode Config::getVideoMode() const
{
    return m_video_mode;
}

void Config::setDefaultVideoMode()
{
    m_video_mode = sf::VideoMode::getDesktopMode();
}

void Config::setDefaultKeybindings()
{
    m_keybindings[Key_Binds::Control::Player_Forwards]  = sf::Keyboard::W;
    m_keybindings[Key_Binds::Control::Player_Back]      = sf::Keyboard::S;
    m_keybindings[Key_Binds::Control::Player_Left]      = sf::Keyboard::A;
    m_keybindings[Key_Binds::Control::Player_Right]     = sf::Keyboard::D;
}

void Config::loadScreenSettingsFromStream(ConfigParser& parser)
{
    while (parser.atKVP())
    {
        auto kvp = parser.getKVP();
        if (kvp.first == "width")
            m_video_mode.width = std::stoi(kvp.second);
        else if (kvp.first == "height")
            m_video_mode.height = std::stoi(kvp.second);
        else
            parser.error("Unrecognised key \"" + kvp.first + "\"");
    }
}

void Config::loadKeybindingsFromStream(ConfigParser& parser)
{
    while (parser.atKVP()) {
        auto kvp = parser.getKVP();
        if (kvp.first == "Player_Forwards")
        {
            m_keybindings[Key_Binds::Control::Player_Forwards] = static_cast<sf::Keyboard::Key>(std::stoi(kvp.second));
        }
        else if (kvp.first == "Player_Back")
        {
            m_keybindings[Key_Binds::Control::Player_Back] = static_cast<sf::Keyboard::Key>(std::stoi(kvp.second));
        }
        else if (kvp.first == "Player_Left")
        {
            m_keybindings[Key_Binds::Control::Player_Left] = static_cast<sf::Keyboard::Key>(std::stoi(kvp.second));
        }
        else if (kvp.first == "Player_Right")
        {
            m_keybindings[Key_Binds::Control::Player_Right] = static_cast<sf::Keyboard::Key>(std::stoi(kvp.second));
        }
        else
        {
            parser.error("Unrecognised key \"" + kvp.first + "\"");
        }
    }
}


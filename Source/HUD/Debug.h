#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>


class MasterRenderer;


///@TODO Right now this only works with floats.
///Needs to work with string, integer, etc
class Debug_HUD
{
    struct Section
    {
        Section(std::string&& format,
                const sf::Vector2f& position,
                const void* info);

        sf::Text        text;
        std::string     format;
        sf::Vector2f    position;
        const void*     info;
    };

    public:
        void addDebugSector(std::string&& format,
                            const void* info);

        void draw(MasterRenderer& master);

    private:
        void drawSection(Section& section, MasterRenderer& master);

        std::vector<Section> m_debugSectors;

        float y = 0;
};

#endif // DEBUG_H_INCLUDED

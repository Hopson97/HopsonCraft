#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

namespace Renderer
{
    class Master;
}

///@TODO Right now this only works with floats. Needs to work with string, integer, etc
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
                            const sf::Vector2f& position,
                            const void* info);

        void draw(Renderer::Master& master);

    private:
        void drawSection(Section& section, Renderer::Master& master);

        std::vector<Section> m_debugSectors;
};

#endif // DEBUG_H_INCLUDED

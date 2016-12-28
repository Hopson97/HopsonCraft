#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <memory>
#include <vector>
#include <cstdint>

class Master_Renderer;
class Panel_Section;

namespace GUI
{
    class Panel
    {
        public:
            Panel();

            void input  ();
            void update ();
            void draw   (Master_Renderer& renderer);

            void addSection(int xPos, int yPos);

        private:
            std::vector<Panel_Section*> m_sections;
    };
}

#endif // PANEL_H_INCLUDED

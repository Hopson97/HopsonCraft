#ifndef COMPONENT_GUI_H
#define COMPONENT_GUI_H

namespace sf
{
    class Event;
}

class Master_Renderer;

namespace GUI
{
    class Component
    {
        public:
            virtual void input  (const sf::Event& e) = 0;
            virtual void update () = 0;
            virtual void draw   (Master_Renderer& renderer) = 0;
    };
}

#endif // COMPONENT_GUI_H

#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "Component.h"

namespace GUI
{
    class Button : public Component
    {
        public:
            Button(const sf::RectangleShape& rect);

        private:

            void input  (const sf::Event& e)    override;
            void update ()                      {}

            virtual void onClick()      = 0;
            virtual void onMouseTouch() = 0;
            virtual void onNoInteract() = 0;

            const sf::RectangleShape& m_rShape;
    };
}

#endif // BUTTON_H

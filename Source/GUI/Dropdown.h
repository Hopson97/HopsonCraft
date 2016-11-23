#ifndef DROPDOWN_H
#define DROPDOWN_H

#include "Component.h"

namespace GUI
{
    class Dropdown : public Component
    {
        public:
            Dropdown(int& optionPtr, const std::vector<std::string>& options);

            void input  (const sf::Event& e)                override;
            void update ()                                  override;
            void draw   (Master_Renderer& renderer)         override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
    };
}

#endif // DROPDOWN_H

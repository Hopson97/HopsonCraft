#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Panel.h"

namespace sf
{
    class Texture;
}


namespace GUI
{
    class Menu : public Panel
    {
        public:
            Menu();

        private:
            void getBackground();
    };
}

#endif // MENU_H_INCLUDED

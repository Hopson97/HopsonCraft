#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML/Graphics.hpp>

#include "Game_State.h"
#include "../GUI/Menu.h"

class Application;
class Camera;
class Master_Renderer;

namespace State
{
    class Main_Menu_State : public Game_State
    {
        public:
            Main_Menu_State(Application& application);

            ~Main_Menu_State();

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt, Camera& camera);
            void draw   (float dt, Master_Renderer& renderer);

            void exitState  ();

        private:
            GUI::Base_Menu m_frontMenu;

            GUI::Base_Menu* m_activeMenu    = nullptr;

            int*            m_seed          = nullptr;
            std::string*    m_worldName     = nullptr;
    };
}

#endif // MENU_STATE_H

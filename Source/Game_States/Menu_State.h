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

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt, Camera& camera);
            void draw   (float dt, Master_Renderer& renderer);

            void exitState  ();

        private:
            uint32_t  getSeed();

            void initFrontMenu  ();
            void initNewGameMenu();

            void genLoadMenu    ();

            GUI::Base_Menu m_frontMenu;
            GUI::Base_Menu m_newGameMenu;
            GUI::Base_Menu m_loadmenu;

            GUI::Base_Menu* m_activeMenu    = nullptr;

            uint32_t   m_seed;
            std::string m_seedString;
            std::string m_worldName;

            sf::Texture m_background;

            bool m_makeWorld = false;

            std::vector<std::string> m_worldFileNames;
            std::map<std::string*, int> m_worldSeeds;
    };
}

#endif // MENU_STATE_H

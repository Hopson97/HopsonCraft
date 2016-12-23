#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML/Graphics.hpp>

#include "Game_State.h"
#include "../GUI/Panel.h"

class Application;
class Entity;
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

            GUI::Panel m_frontMenu;
            GUI::Panel m_newGameMenu;
            GUI::Panel m_loadmenu;

            GUI::Panel* m_activeMenu    = nullptr;

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

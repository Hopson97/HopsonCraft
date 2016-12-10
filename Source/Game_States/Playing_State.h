#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <SFML/Graphics.hpp>

#include "../Input/Function_Toggle_Key.h"
#include "../Renderer/Master_Renderer.h"
#include "../World/Chunk/Chunk_Map.h"
#include "../Player/Player.h"
#include "../GUI/Panel.h"
#include "../Crosshair.h"
#include "Game_State.h"

class Entity;
class Application;

namespace State
{
    class Playing_State : public Game_State
    {
        enum class PS_State //Playing State State xD
        {
            Play,
            Pause,
            Block_Menu,
        };

        enum class RenderDistance
        {
            Tiny = 3,
            Small = 8,
            Medium = 15,
            Far = 20,
        };

        public:
            Playing_State  (Application& application,
                            const std::string& worldName,
                            uint32_t seed);

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt, Entity& camera);
            void draw   (float dt, Master_Renderer& renderer);

            void exitState  ();

        private:
            void blockEdit();

            void tryAddPostFX(Master_Renderer& renderer);

            void prepareExit(Master_Renderer& renderer);

            void setUpPauseMenu();
            void setUpSettingsMenu();

            void loadWorldFile();
            void loadWorldList();

            void save();
            void saveWorldFile();
            void saveWorldList();

            std::unique_ptr<Chunk_Map> m_chunkMap;

            Player          m_player;
            Chunk_Location  m_playerPosition;

            bool m_debugDisplayActive = false;

            Function_Toggle_Key m_debugDisplay;

            std::string m_worldName;
            uint32_t   m_worldSeed;

            GUI::Panel m_pauseMenu;
            GUI::Panel m_settingsMenu;

            GUI::Panel* m_activeMenu;


            PS_State m_state = PS_State::Play;
            bool m_isExitGame = false;

            std::vector<std::string> m_worldFileNames;

            Crosshair m_crosshair;

            sf::Clock m_autoSaveTimer;
    };
}


#endif // PLAYING_STATE_H

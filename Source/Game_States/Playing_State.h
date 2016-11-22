#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <SFML/Graphics.hpp>

#include "Game_State.h"

#include "../Player/Player.h"
#include "../Renderer/Master_Renderer.h"
#include "../Input/Function_Toggle_Key.h"
#include "../World/Chunk/Chunk_Map.h"

#include "Menu.h"

class Camera;
class Application;

namespace State
{
    class Playing_State : public Game_State
    {
        enum class State_t
        {
            Play,
            Pause
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
            void update (float dt, Camera& camera);
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

            void saveWorldFile();
            void saveWorldList();

            std::unique_ptr<Chunk_Map> m_chunkMap;

            Player          m_player;
            Chunk_Location  m_playerPosition;

            bool m_debugDisplayActive = false;

            Function_Toggle_Key m_debugDisplay;

            sf::Texture crossHairTexture;
            sf::Sprite crossHairSprite;

            std::string m_worldName;
            uint32_t   m_worldSeed;

            GUI::Base_Menu m_pauseMenu;
            GUI::Base_Menu m_settingsMenu;

            GUI::Base_Menu* m_activeMenu;


            State_t m_state = State_t::Play;
            bool exitGame = false;

            std::vector<std::string> m_worldFileNames;
    };
}


#endif // PLAYING_STATE_H

#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <SFML/Graphics.hpp>

#include "../Input/Function_Toggle_Key.h"
#include "../Renderer/Master_Renderer.h"
#include "../Mob/Player.h"
#include "../GUI/Panel.h"
#include "../Crosshair.h"
#include "../World/World.h"
#include "Game_State.h"

class Camera;
class Application;

namespace State
{
    class Playing_State : public Game_State
    {
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
            void tryAddPostFX(Master_Renderer& renderer);

            void prepareExit(Master_Renderer& renderer);

            void loadWorldList();

            void save();
            void saveWorldList();

            bool m_debugDisplayActive = false;
            Function_Toggle_Key m_debugDisplay;

            std::string m_worldName;
            uint32_t   m_worldSeed;

            std::vector<std::string> m_worldFileNames;

            std::unique_ptr<World> m_world;

            bool m_isPaused = false;
    };
}


#endif // PLAYING_STATE_H

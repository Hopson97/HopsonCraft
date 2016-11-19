#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <SFML/Graphics.hpp>

#include "Game_State.h"

#include "../Player/Player.h"
#include "../Renderer/Master_Renderer.h"
#include "../Input/Function_Toggle_Key.h"
#include "../World/Chunk/Chunk_Map.h"

class Camera;
class Application;

namespace State
{
    class Playing_State : public Game_State
    {
        public:
            Playing_State  (Application& application,
                            const std::string& worldName,
                            unsigned seed);

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt, Camera& camera);
            void draw   (float dt, Master_Renderer& renderer);

            void exitState  ();

        private:
            void blockEdit();

            std::unique_ptr<Chunk_Map> m_chunkMap;

            Player          m_player;
            Chunk_Location  m_playerPosition;

            bool m_debugDisplayActive = false;

            Function_Toggle_Key m_debugDisplay;

            sf::Texture crossHairTexture;
            sf::Sprite crossHairSprite;

            std::string m_worldName;
            unsigned    m_worldSeed;
    };
}


#endif // PLAYING_STATE_H

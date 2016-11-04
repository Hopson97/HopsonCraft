#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "Game_State.h"
#include "Player.h"
#include "Chunk/Chunk_Map.h"
#include "Master_Renderer.h"
#include "Input/Function_Toggle_Key.h"

#include <SFML/Graphics.hpp>

class Application;

namespace State
{
    class Playing_State : public Game_State
    {
        public:
            Playing_State  (Application& application);

            void input  (float dt) override;
            void update (float dt) override;
            void draw   (float dt) override;
            void sfDraw (float dt) override;

        private:
            Player          m_player;
            Chunk_Location  m_playerPosition;
            Chunk_Map       m_chunkMap;
            Master_Renderer m_renderer;

            bool m_debugDisplayActive = false;

            Function_Toggle_Key m_debugDisplay;

            sf::Texture crossHairTexture;
            sf::Sprite  crossHairSprite;
    };
}


#endif // PLAYING_STATE_H

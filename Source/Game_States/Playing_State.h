#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <SFML/Graphics.hpp>

#include "Game_State.h"

#include "../Player/Player.h"

#include "../Renderer/Master_Renderer.h"

#include "../Input/Function_Toggle_Key.h"

#include "../World/Chunk/Chunk_Map.h"
#include "../World/Chunk/Chunk.h"


class Application;

namespace State
{
    class Playing_State : public Game_State
    {
        public:
            Playing_State  (Application& application);

            void input      (float dt)  override;
            void update     (float dt, Camera& camera)  override;
            void draw       (float dt, Master_Renderer& renderer)  override;

            void exitState  ()          override;

        private:
            void blockEdit();

            Player          m_player;
            Chunk_Location  m_playerPosition;
            Chunk_Map       m_chunkMap;


            bool m_debugDisplayActive = false;

            Function_Toggle_Key m_debugDisplay;

            sf::Texture crossHairTexture;
            sf::Sprite  crossHairSprite;
    };
}


#endif // PLAYING_STATE_H

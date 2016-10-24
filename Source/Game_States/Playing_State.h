#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "Game_State.h"
#include "Player.h"

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

        private:
            Application* m_application;
            Player m_player;
    };
}


#endif // PLAYING_STATE_H

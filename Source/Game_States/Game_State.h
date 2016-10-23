#ifndef GAME_STATE_H
#define GAME_STATE_H

//this is the base class

class Application;

namespace State
{
    class Game_State
    {
        public:
            Game_State  (Application& application);

            virtual void input  (float dt) = 0;
            virtual void update (float dt) = 0;
            virtual void draw   (float dt) = 0;

        protected:
            Application* m_application; //fuck da police
    };
}

#endif // GAME_STATE_H

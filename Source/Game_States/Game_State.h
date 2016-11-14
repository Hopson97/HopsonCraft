#ifndef GAME_STATE_H
#define GAME_STATE_H

//this is the base class

class Application;
class Camera;
class Master_Renderer;

namespace State
{
    class Game_State
    {
        public:
            Game_State  (Application& application);
            virtual ~Game_State(){}

            virtual void input      (float dt)  = 0;
            virtual void update     (float dt, Camera& camera)  = 0;
            virtual void draw       (float dt, Master_Renderer& renderer)  = 0;
            virtual void exitState  ()          = 0;

        protected:
            Application* m_application; //fuck da police
    };
}

#endif // GAME_STATE_H

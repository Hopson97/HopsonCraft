#include "playing_state.h"

namespace State
{
    Playing_State::Playing_State(Application& application)
    :   Game_State (application)
    { }

    void Playing_State::input  (float dt)
    {
        m_player.input();
    }

    void Playing_State::update (float dt)
    {
        m_player.update(dt);
    }

    void Playing_State::draw   (float dt)
    {

    }
}

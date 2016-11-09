#ifndef PLAYER_H
#define PLAYER_H


#include "OpenGL/Glm/glm_transformations.h"
#include "Camera.h"
#include "Function_Toggle_Key.h"
#include <SFML/Graphics.hpp>

namespace Block
{
    class Block_Base;
}

class Player
{
    public:
        Player ();
        void input  ();
        void update (float dt);

        const Camera&   getCamera   () const;
        const Vector3&  getPosition () const;
        const Vector3&  getRotation () const;

        void setPosition (const Vector3& position);
        void setRotation (const Vector3& rotation);

        Block::Block_Base& getHeldBlock ();

        constexpr static float ACC = 0.4;

    private:
        void movementInput();
        void toggleInput();

        void switchBlock (int inc);

        Vector3 m_velocity;

        Camera m_camera;

        Function_Toggle_Key m_rotationLock;
        bool m_isRotLocked = false;

        bool m_canChangeBlock = true;
        Function_Toggle_Key m_increaseBlockToggle;
        Function_Toggle_Key m_decreaseBlockToggle;


        Block::Block_Base* m_heldBlock;
};

#endif // PLAYER_H

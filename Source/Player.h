#ifndef PLAYER_H
#define PLAYER_H


#include "OpenGL/Glm/glm_transformations.h"
#include "Camera.h"
#include "Input/Toggle_Key.h"
#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player ();
        void input  ();
        void update (float dt);

        const Camera&   getCamera   () const;
        const Vector3&  getPosition () const;
        const Vector3&  getRotation () const;

        constexpr static float ACC = 0.3;

    private:
        Vector3 m_velocity;

        Camera m_camera;

        Toggle_Key m_rotationLock;
        bool m_isRotLocked = false;
};

#endif // PLAYER_H

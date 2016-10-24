#ifndef PLAYER_H
#define PLAYER_H


#include "OpenGL/Glm/glm_transformations.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>

class Player
{
    public:
        void input  ();
        void update (float dt);

        const Camera&   getCamera   () const;
        const Vector3&  getPosition () const;
        const Vector3&  getRotation () const;

        constexpr static float ACC = 0.3;

    private:


        Vector3 m_velocity;

        Camera m_camera;
};

#endif // PLAYER_H

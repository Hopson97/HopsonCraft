#ifndef CAMERA_H
#define CAMERA_H

#include "OpenGL/GLM/glm_transformations.h"
#include <SFML/Graphics.hpp>

class Camera
{
    public:
        const Vector3& getPosition () const;
        const Vector3& getRotation () const;

        void movePosition ( const Vector3& position );

        void move ( float dt );
        void update ();



    private:
        Vector3 m_position;
        Vector3 m_rotation = { 90, 0, 0 };

        sf::Vector2i m_lastMosuePos;
};

#endif // CAMERA_H

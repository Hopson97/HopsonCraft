#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"
#include "Maths/Frustum.h"

class Camera : public Entity
{
    public:
        Camera();


        void setFOV     (float FOV);
        float getFOV    () const;

        void update         ();
        void hookEntity     (const Entity& entity);
        void unhookEntity   ();

        const Frustum& getFrustum() const;

        const Matrix4& getProjectionViewMatrix() const;

    private:
        const Entity* m_P_entity = this;
        Frustum m_frustum;

        float m_fov = 100;

        Matrix4 m_viewMatrix;
        Matrix4 m_projectionMatrix;
        Matrix4 m_projectionViewMatrix;
};

#endif // CAMERA_H_INCLUDED

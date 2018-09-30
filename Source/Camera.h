#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity/Entity.h"
#include "Maths/Frustum.h"

class Camera : public Entity
{
    public:
        Camera() noexcept;


        void setFOV     (float FOV)                 noexcept;
        float getFOV    () const                    noexcept;

        void update         ()                      noexcept;
        void hookEntity     (const Entity& entity)  noexcept;
        void unhookEntity   ()                      noexcept;

        const Frustum& getFrustum() const noexcept;

        const Matrix4& getProjectionViewMatrix  () const noexcept;
        const Matrix4& getViewMatrix            () const noexcept;
        const Matrix4& getProjMatrix            () const noexcept;

    private:
        const Entity* m_pEntity = nullptr;
        Frustum m_frustum;

        float m_fov = 100;

        Matrix4 m_viewMatrix;
        Matrix4 m_projectionMatrix;
        Matrix4 m_projectionViewMatrix;
};

#endif // CAMERA_H_INCLUDED

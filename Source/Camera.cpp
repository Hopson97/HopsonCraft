#include "Camera.h"

#include <cmath>
#include <iostream>

#include "Maths/Matrix.h"

Camera::Camera()
{
    m_projectionMatrix = Maths::createProjMatrix(m_fov);
}

void Camera::setFOV(float FOV)
{
    m_fov = FOV;
    m_projectionMatrix = Maths::createProjMatrix(m_fov);
}

float Camera::getFOV() const
{
    return m_fov;
}

void Camera::unhookEntity()
{
    m_pEntity = nullptr;
}

void Camera::update()
{
    if(m_pEntity)
    {
        position = m_pEntity->position;
        rotation = m_pEntity->rotation;
    }

    m_viewMatrix = Maths::createViewMatrix(*this);

    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    m_frustum.update(m_projectionViewMatrix);
}

void Camera::hookEntity(const Entity& entity)
{
    m_pEntity = &entity;
    update();
}

const Frustum& Camera::getFrustum() const
{
    return m_frustum;
}

const Matrix4& Camera::getProjectionViewMatrix() const
{
    return m_projectionViewMatrix;
}

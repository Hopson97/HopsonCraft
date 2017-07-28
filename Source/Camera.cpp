#include "Camera.h"

#include <cmath>
#include <iostream>

#include "Maths/Matrix.h"

Camera::Camera() noexcept
{
    m_projectionMatrix = createProjMatrix(m_fov);
}

void Camera::setFOV(float FOV) noexcept
{
    m_fov = FOV;
    m_projectionMatrix = createProjMatrix(m_fov);
}

float Camera::getFOV() const  noexcept
{
    return m_fov;
}

void Camera::unhookEntity()  noexcept
{
    m_pEntity = nullptr;
}

void Camera::update() noexcept
{
    if(m_pEntity)
    {
        position = m_pEntity->position;
        rotation = m_pEntity->rotation;
    }

    m_viewMatrix = createViewMatrix(*this);

    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    m_frustum.update(m_projectionViewMatrix);
}

void Camera::hookEntity(const Entity& entity) noexcept
{
    m_pEntity = &entity;
    update();
}

const Frustum& Camera::getFrustum() const noexcept
{
    return m_frustum;
}

const Matrix4& Camera::getProjectionViewMatrix() const noexcept
{
    return m_projectionViewMatrix;
}

const Matrix4& Camera::getViewMatrix() const noexcept
{
    return m_viewMatrix;
}

const Matrix4& Camera::getProjMatrix() const noexcept
{
    return m_projectionMatrix;
}


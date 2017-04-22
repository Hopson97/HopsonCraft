#include "Camera.h"

#include <cmath>
#include <iostream>

#include "Maths/Matrix_Maths.h"

Camera::Camera()
{
    m_projectionMatrix = Maths::createProjMatrix(110);
}

void Camera::update()
{
    position = m_P_entity->position;
    rotation = m_P_entity->rotation;

    m_viewMatrix = Maths::createViewMatrix(*this);

    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    m_frustum.update(m_projectionViewMatrix);
}

void Camera::hookEntity(const Entity& entity)
{
    m_P_entity = &entity;
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
